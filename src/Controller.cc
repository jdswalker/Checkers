// Authors: @ColinVDH and @JDSWalker
// Created on: 11/10/16
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=c++11 -Wall -Werror -c Controller.cc -o Controller.o

#include <algorithm>  // transform
#include <array>      // array
#include <chrono>     // sleep_for(), milliseconds()
#include <iostream>   // cin, getline
#include <thread>     // this_thread
#include <cstdlib>    // toTile()
#include <map>        // map
#include <memory>     // shared_ptr<>(), make_shared<>()
#include <string>     // string, tolower

#include "Colour.h"
#include "GameUI.h"
#include "HumanPlayer.h"
#include "Player.h"

#include "Controller.h"

// PUBLIC METHODS
Controller::Controller() {
  gameUI = std::make_shared<GameUI>(GameUI());
}

void Controller::StartGame() {
  while(true) {
    gameUI->MainMenu();

    if (GetGameMode() == GameMode::TWOPLAYER) {
      board = std::make_shared<GameBoard>(GameBoard());
      player1 = std::make_shared<HumanPlayer>(HumanPlayer(Colour::DARK));
      player2 = std::make_shared<HumanPlayer>(HumanPlayer(Colour::LIGHT));
    }
   
    activePlayer = player1;
    gameUI->InitUI(board, player1, player2);

    while ( CheckLose() ) {
      bool legalMoveFound = false;
      bool lastMoveWasLegal = true;
      
      while ( not legalMoveFound ) {
        /*
        if ( (mode == GameMode::TWOPLAYER and activePlayer == player2) or
             (mode == GameMode::PLAYERCOMPUTER and not player2->IsHuman()) ) {
        }
        */
        gameUI->UpdateBoard(lastMoveWasLegal);
        GetValidInput();
        
        lastMoveWasLegal = true; // Stops turn increment in UI when false

        if ( IsLegalMove(activePlayer->GetMove()) ){
          legalMoveFound = true;
          ExecuteMove(activePlayer->GetMove());
        } else {
          lastMoveWasLegal = false;
          ShowError(GameError::ILLEGAL, 2000);
        }
      }
      
      // Switch active player
      activePlayer = (activePlayer == player1) ? player2 : player1;
    }
    
    gameUI->EndGame(activePlayer != player1);
    
    if( not PlayAgain() )
      break;
  }
}

void Controller::GetValidInput() {
  if (activePlayer->IsHuman()) {
    activePlayer->SetInput();
    
    while (not activePlayer->HasValidInput()){
      ShowError(GameError::INVALID, 500);
      gameUI->UpdateBoard(false);
      activePlayer->SetInput();
    }
    
    if (activePlayer->GetInput() == "q") {
      std::exit(0);
    }
  }
}

// PRIVATE METHODS

GameMode Controller::GetGameMode() {  
  std::map< std::string, unsigned int > userChoice = {
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
      std::exit(0);
    }
    case 1: {
      return GameMode::PLAYERCOMPUTER;
    }
    case 2: {
      return GameMode::TWOPLAYER;
    }
    default: {
      ShowError(GameError::INVALID, 500);
      gameUI->MainMenu();
      return GetGameMode();
    }
  }
}

std::string Controller::GetInput() {
  std::string input;
  std::getline(std::cin, input, '\n');
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  return input;
}

void Controller::ShowError(GameError errorType, int time){
  switch(errorType) {
    case GameError::INVALID: {
      gameUI->InvalidInputMessage();
      break;
    }
    case GameError::ILLEGAL: {
      gameUI->IllegalMoveMessage();
      break;
    }
  }
  
  PauseGame(time);
}

void Controller::PauseGame(int time) {
  if ( time == 0 ) {
    std::cin.get();
  } else {
    std::this_thread::sleep_for( std::chrono::milliseconds(time) );
  }
}

bool Controller::IsLegalMove(Move currMove) {
  std::array<int, 2> start = currMove.GetFirst();
  std::array<int, 2> fromTile = {start[0], start[1]}; 
  std::array<int, 2> toTile;

  if (board->GetPiece(start) == nullptr){
    return false;
  }

  if (board->GetPiece(start)->GetColour() != activePlayer->GetColour()) {
    return false;
  }
  
  // Check for open space 2 squares away
  if (currMove.GetLength() == 2) {
    toTile = currMove.GetNext();
    
    bool legalSlide = board->IsLegalSlide( fromTile, toTile );
    bool possibleJumps = board->JumpsAvailable( activePlayer->GetColour() );
    
    if (legalSlide and not possibleJumps) {
      return true;
    }
    // AFTER JUMPING NEED TO CHECK FOR ADDITIONAL POSSIBLE JUMPS?
    if ( board->IsLegalJump(board->GetPiece(start), fromTile, toTile) ) {
      return true;
    }
  } else {
    while (currMove.HasNext()) {
      toTile = currMove.GetNext();
      if ( not board->IsLegalJump(board->GetPiece(start), fromTile, toTile) )
        return false;

      fromTile = toTile;
    }
    // AFTER JUMPING NEED TO CHECK FOR ADDITIONAL POSSIBLE JUMPS?
    return true;
  }

  return false;
}

bool Controller::PlayAgain() {
  std::string input;
  
  while (true) {
    input = GetInput();
    if (input == "q" || input == "quit" || input == "exit" ||
        input == "n" || input == "no" ) {
      exit(0);
    } else if (input == "y" || input == "yes") {
      return true;
    } else {
      ShowError(GameError::INVALID, 1);
    }
  }
}

bool Controller::CheckLose() {
  Colour playerColour = activePlayer->GetColour();
  
  bool canMoveAPiece = board->MovesRemaining(playerColour);
  bool hasPiecesLeft = board->PiecesRemaining(playerColour);
  
  return canMoveAPiece or hasPiecesLeft;
}

void Controller::ExecuteMove(Move action) {
  std::array<int,2> fromTile = action.GetFirst();
  std::array<int,2> toTile;
  
  if (action.GetLength() == 2) {
    toTile = action.GetNext();
    if ( not board->IsLegalSlide(fromTile, toTile) ) {
      board->RemovePiece({
        (toTile[0]+fromTile[0])/2,
        (toTile[1]+fromTile[1])/2
      });
    }
    board->MovePiece(fromTile,toTile);
  } else {
    
    while(action.HasNext()) {
      toTile = action.GetNext();
      
      board->RemovePiece({
        (toTile[0]+fromTile[0])/2,
        (toTile[1]+fromTile[1])/2
      });
      board->MovePiece(fromTile, toTile);
      
      fromTile = toTile;       
    }
  }
}
