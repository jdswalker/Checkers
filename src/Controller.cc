// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c Controller.cc -o Controller.o

#include <algorithm>  // transform
#include <iostream>   // cin, getline
#include <map>        // map
#include <memory>     // shared_ptr, make_shared, dynamic_pointer_cast
#include <string>     // string, tolower
#include <vector>     // vector
#include <utility>    // pair

#include "Colour.h"
#include "Controller.h"
#include "GameBoard.h"
#include "GameError.h"
#include "GameMode.h"
#include "GameUI.h"
#include "Player.h"
#include "PlayerAI.h"
#include "PlayerHuman.h"

// PUBLIC METHODS
// Constructor
Controller::Controller() {
  gameUI = std::make_shared<GameUI>(GameUI());
}

// This method controls the behaviour and execution of the game
void Controller::StartGame() {
  while(true) {
    
    // Output main game menu
    gameUI->OutputMainMenu();

    // Initialize checkers board
    board = std::make_shared<GameBoard>(GameBoard());
    
    // Player with DARK pieces goes first, so automatically assign to human
    player1 = std::make_shared<PlayerHuman>(PlayerHuman(Colour::DARK));
    
    // Based on Game Mode, assign second player to LIGHT coloured pieces
    switch (GetGameMode()) {
      case GameMode::PLAYER_VS_PLAYER: {
        player2 = std::make_shared<PlayerHuman>(PlayerHuman(Colour::LIGHT));
        break;
      }
      case GameMode::PLAYER_VS_COMPUTER: {
        player2 = std::make_shared<PlayerAI>(
            PlayerAI(Colour::LIGHT, board));
        break;
      }
      default: {
        std::cerr << "ERROR: Game mode not recognized\n" << std::endl;
        std::exit(1);
      }
    }

    // Dark coloured pieces (i.e., player 1) always has the first move
    activePlayer = player1;
    gameUI->InitUI(board, player1, player2);

    // Loops once per turn, each time checking if the game is over
    while ( GameHasMoreTurns() ) {
      bool legalMoveFound = false;
      bool lastMoveWasLegal = true;
      
      while ( not legalMoveFound ) {

        gameUI->OutputGameBoard(lastMoveWasLegal);
        GetValidInput();
        
        // Stops turn increment in UI when false
        lastMoveWasLegal = true;

        if ( IsLegalMove(activePlayer->GetMove()) ){
          legalMoveFound = true;
          ExecuteMove(activePlayer->GetMove());
        } else {
          lastMoveWasLegal = false;
          gameUI->OutputErrorMessage(GameError::ILLEGAL_MOVE);
        }
      }
      
      // Switch active player
      activePlayer = (activePlayer == player1) ? player2 : player1;
    }
    
    gameUI->OutputGameOver(activePlayer != player1);
    
    if( not PlayAgain() ) {
      gameUI->OutputQuitProgram();
      break;
    }
  }
}

// PRIVATE METHODS
// Determines main menu options/behaviour
GameMode Controller::GetGameMode() {  
  std::map< std::string, int > userChoice = {
    { "1",    1 },
    { "2",    2 },
    { "q",    0 },
    { "quit", 0 },
    { "exit", 0 },
    { "3",    0 }
  };
  std::string input = GetInput();
  
  switch(userChoice[input]) {
    case 0: {
      gameUI->OutputQuitProgram();
      std::exit(0);
    }
    case 1: {
      return GameMode::PLAYER_VS_COMPUTER;
    }
    case 2: {
      return GameMode::PLAYER_VS_PLAYER;
    }
    default: {
      gameUI->OutputErrorMessage(GameError::INVALID_INPUT);
      gameUI->OutputMainMenu();
      return GetGameMode();
    }
  }
}

// Gets game play based input from user and checks if it is valid
void Controller::GetValidInput() {

  if (activePlayer->IsHuman()) {
    // Cast is needed since SetInput() is not defined for the base Player class
    std::dynamic_pointer_cast<PlayerHuman>(activePlayer)->SetInput();
    
    while (not std::dynamic_pointer_cast<PlayerHuman>
        (activePlayer)->HasValidInput()) {
      
      gameUI->OutputErrorMessage(GameError::INVALID_INPUT);
      // Turn does not increment while invalid input is provided
      gameUI->OutputGameBoard(false);
      
      std::dynamic_pointer_cast<PlayerHuman>(activePlayer)->SetInput();
    }
    
    std::string input = std::dynamic_pointer_cast<PlayerHuman>
        (activePlayer)->GetInput();
    
    if (   input == "q"
        or input == "quit"
        or input == "exit") {

      gameUI->OutputQuitProgram();
      std::exit(0);
    }
  }
}

// Gets user input for non-game related options
std::string Controller::GetInput() {
  
  std::string input;
  std::getline(std::cin, input, '\n');
  
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  
  return input;
}

// Checks if the move sequence conforms to the game rules
bool Controller::IsLegalMove(Move play) {

  bool moveIsLegal = false;
  auto allValidMoves = board->GetAllValidMoves(activePlayer->GetColour());
  
  for (const auto &validMove : allValidMoves) {
    if (play == validMove) {
      moveIsLegal = true;
      break;
    }
  }
  
  return moveIsLegal;
}

// This method carries out the given (and assumed valid) sequence of moves
void Controller::ExecuteMove(Move play) {

  std::pair<int,int> fromTile = play.GetFirst();
  std::pair<int,int> toTile;
  
  // Single slide or jump move sequence
  if (play.GetMoveSequenceLength() == 2) {
    toTile = play.GetNext();
    if (not board->IsLegalSlide(board->GetPiece(fromTile), fromTile, toTile)) {
      board->RemovePiece({
        (fromTile.first  + toTile.first)  / 2,
        (fromTile.second + toTile.second) / 2
      });
    }
    board->MovePiece(fromTile, toTile);
    
  // Multiple jump move sequence
  } else {
    
    while(play.HasAnotherMove()) {
      toTile = play.GetNext();
      
      board->RemovePiece({
        (fromTile.first  + toTile.first)  / 2,
        (fromTile.second + toTile.second) / 2
      });
      board->MovePiece(fromTile, toTile);
      
      fromTile = toTile;       
    }
  }
}

// Checks whether the active player has any possible moves (if not, they lose)
bool Controller::GameHasMoreTurns() {
  auto playerColour = activePlayer->GetColour();
  
  bool canMoveAPiece = board->MovesRemaining(playerColour);
  bool hasPiecesLeft = board->PiecesRemaining(playerColour);
  
  return canMoveAPiece or hasPiecesLeft;
}

// Queries the user for whether they want to play another game
bool Controller::PlayAgain() {

  while (true) {
    auto input = GetInput();
    if (   input == "q"
        or input == "quit"
        or input == "exit"
        or input == "n"
        or input == "no" ) {

      return false;

    } else if (   input == "y"
               or input == "yes") {

      return true;

    } else {

      gameUI->OutputErrorMessage(GameError::INVALID_INPUT);
    }
  }
}
