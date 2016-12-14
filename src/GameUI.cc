// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c GameUI.cc -o GameUI.o

#include <iostream>   // cout, endl, ostream
#include <memory>     // shared_ptr, make_shared
#include <sstream>    // ostringstream
#include <string>     // string
#include <typeinfo>   // typeid

#include "GameBoard.h"
#include "GameUI.h"
#include "GameError.h"
#include "Player.h"

// Constructor
GameUI::GameUI() {
  board = nullptr;
  player1 = nullptr;
  player2 = nullptr;
  turn_number = 0;
}

// User Interface Initialization
void GameUI::InitUI(std::shared_ptr<GameBoard> newBoard,
                    std::shared_ptr<Player> newPlayer1,
                    std::shared_ptr<Player> newPlayer2) {

  board = newBoard;
  player1 = newPlayer1;
  player2 = newPlayer2;
}

// Outputs the game header and game menu options
void GameUI::OutputMainMenu() {

  const std::string welcome = 
      " ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗ \n"
      " ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝ \n"
      " ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗   \n"
      " ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝   \n"
      " ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗ \n"
      "  ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝ \n"
      "                      ████████╗ ██████╗                         \n"
      "                      ╚══██╔══╝██╔═══██╗                        \n"
      "                         ██║   ██║   ██║                        \n"
      "                         ██║   ██║   ██║                        \n"
      "                         ██║   ╚██████╔╝                        \n"
      "                         ╚═╝    ╚═════╝                         \n"
      " ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ ███████╗\n"
      "██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝\n"
      "██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝███████╗\n"
      "██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║\n"
      "╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║███████║\n"
      " ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n";

  const std::string menuOptions =
      "Main Menu Options:\n"
      "  1. Play with a computer opponent\n"
      "  2. Play with another person\n"
      "  3. Quit\n"
      "Enter a number to choose: ";

  std::cout << welcome << std::endl << menuOptions;
}

// Updates the UI displayed for the user based on which players turn it is
void GameUI::OutputGameBoard(bool updateTurn) {
  
  // Stops incrementing if the last move was invalid
  if (updateTurn) {
    turn_number += 1;
  }
  
  std::ostringstream output;

  // Game play header
  if (typeid(player1) == typeid(player2)) {
    output << "CHECKERS: Two-Player Mode       Turn: " << turn_number << "\n\n";
  } else {
    output << "CHECKERS: One-Player Mode       Turn: " << turn_number << "\n\n";
  }
  
  // Top-left and bottom-right are both light coloured tiles
  bool isLightBoardTile = true;
  
  // See https://en.wikipedia.org/wiki/ANSI_escape_code#Colors for color info
  std::string darkBoardTile =  "\033[40m   \033[0m";
  std::string lightBoardTile = "\033[47m   \033[0m";

  // Game board rendering
  output << "    1  2  3  4  5  6  7  8 \n\n";
  for (auto row = 0; row < 8; ++row) {
    output << static_cast<char>('A' + row) << "  ";
    for (auto column = 0; column < 8; ++column) {
      if (isLightBoardTile) {
        output << lightBoardTile;
      } else if (board->GetPiece(row, column) == nullptr) {
        output << darkBoardTile;
      } else {
        output << *(board->GetPiece(row, column));
      }
      isLightBoardTile = not isLightBoardTile;
    }
    output << "  " << static_cast<char>('A' + row) << std::endl;

    isLightBoardTile = not isLightBoardTile;
  }
  output << "\n    1  2  3  4  5  6  7  8 \n" << std::endl;
  
  // Footer
  output << "Enter a sequence of coordinates to move a piece\n"
         << "  e.g., 'F1 D4 B1' would be a double jump\n";
  if (turn_number % 2 == 1)
    output << "\033[1;31;40mPlayer One's Move:\033[0m ";
  else
    output << "\033[1;40mPlayer Two's Move:\033[0m ";
  
  std::cout << "\n\n" << output.str();
}

// Outputs the game over message depending on which player won
void GameUI::OutputGameOver(bool player1_wins_game) {
  
  const std::string winForPlayer1 = "\n\n\n"
      "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      ██╗\n"
      "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ███║\n"
      "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝    ╚██║\n"
      "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║\n"
      "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ██║\n"
      "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     ╚═╝\n"
      "        ██╗    ██╗██╗███╗   ██╗███████╗██╗██╗██╗         \n"
      "        ██║    ██║██║████╗  ██║██╔════╝██║██║██║         \n"
      "        ██║ █╗ ██║██║██╔██╗ ██║███████╗██║██║██║         \n"
      "        ██║███╗██║██║██║╚██╗██║╚════██║╚═╝╚═╝╚═╝         \n"
      "        ╚███╔███╔╝██║██║ ╚████║███████║██╗██╗██╗         \n"
      "         ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝╚═╝         \n";
  
  const std::string winForPlayer2 = "\n\n\n"
      "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗ \n"
      "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗\n"
      "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝\n"
      "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗    ██╔═══╝ \n"
      "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ███████╗\n"
      "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚══════╝\n"
      "        ██╗    ██╗██╗███╗   ██╗███████╗██╗██╗██╗             \n"
      "        ██║    ██║██║████╗  ██║██╔════╝██║██║██║             \n"
      "        ██║ █╗ ██║██║██╔██╗ ██║███████╗██║██║██║             \n"
      "        ██║███╗██║██║██║╚██╗██║╚════██║╚═╝╚═╝╚═╝             \n"
      "        ╚███╔███╔╝██║██║ ╚████║███████║██╗██╗██╗             \n"
      "         ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝╚═╝             \n";
  
  const std::string askToPlayAgain = "Would you like to play again? (y or n): ";
  
  if ( player1_wins_game ) {
    std::cout << winForPlayer1 << std::endl;
  } else {
    std::cout << winForPlayer2 << std::endl;
  }
  
  std::cout << askToPlayAgain;
}

// Output when quiting the program
void GameUI::OutputQuitProgram() {

  const std::string clearScreen = std::string(75, '\n');

  const std::string quitProgramMessage =
      "  ████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗███████╗  \n"
      "  ╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝██╔════╝  \n"
      "     ██║   ███████║███████║██╔██╗ ██║█████╔╝ ███████╗  \n"
      "     ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗ ╚════██║  \n"
      "     ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗███████║  \n"
      "     ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝  \n"
      "               ███████╗ ██████╗ ██████╗                \n"
      "               ██╔════╝██╔═══██╗██╔══██╗               \n"
      "               █████╗  ██║   ██║██████╔╝               \n"
      "               ██╔══╝  ██║   ██║██╔══██╗               \n"
      "               ██║     ╚██████╔╝██║  ██║               \n"
      "               ╚═╝      ╚═════╝ ╚═╝  ╚═╝               \n"
      "██████╗ ██╗      █████╗ ██╗   ██╗██╗███╗   ██╗ ██████╗ \n"
      "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██║████╗  ██║██╔════╝ \n"
      "██████╔╝██║     ███████║ ╚████╔╝ ██║██╔██╗ ██║██║  ███╗\n"
      "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██║██║╚██╗██║██║   ██║\n"
      "██║     ███████╗██║  ██║   ██║   ██║██║ ╚████║╚██████╔╝\n"
      "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ \n";

  std::cout << clearScreen << quitProgramMessage << std::endl;
}

// Controls output for error messages
void GameUI::OutputErrorMessage(GameError errorType) {
  
  std::string errorMessage = "\n\033[31mERROR\033[0m: ";
  
  switch(errorType) {
    // Output when user input cannot be parsed
    case GameError::INVALID_INPUT: {
      errorMessage += "Invalid input provided";
      break;
    }
    // Output when user input can be parsed, but violates one of the game rules
    case GameError::ILLEGAL_MOVE: {
      errorMessage += "Illegal move attempted";
      break;
    }
  }
  
  std::cout << errorMessage << std::endl;
}
