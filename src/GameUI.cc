// Created by Colin on 11/10/16.
// Authors: @ColinVDH and @JDSWalker
// Created on: 11/10/16
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compiled using: g++ -std=c++11 -Wall -Werror -c GameUI.cc -o GameUI.o

#include <iostream> // cout, cerr, ostream
#include <memory>  // shared_ptr<>(), make_shared<>()
#include <sstream> // 
#include <string>
#include <typeinfo>

#include "GameBoard.h"
#include "GameError.h"
#include "Player.h"

#include "GameUI.h"

GameUI::GameUI() {
  board = nullptr;
  player1 = nullptr;
  player2 = nullptr;
  turn_number = 0;
  board_is_flipped_up = false;
}

void GameUI::InitUI(std::shared_ptr<GameBoard> newBoard, std::shared_ptr<Player> newPlayer1, std::shared_ptr<Player> newPlayer2) {
  board = newBoard;
  player1 = newPlayer1;
  player2 = newPlayer2;
}

void GameUI::MainMenu() {
  std::string welcome = "";
  std::string menuOptions = "";

  welcome = "\n\n"
            " ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ ███████╗\n"
            "██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝\n"
            "██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝███████╗\n"
            "██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║\n"
            "╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║███████║\n"
            " ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n"
            "\n";

  menuOptions = "Main Menu Options:\n"
                "  1. Play Checkers with a computer opponent\n"
                "  2. Play Checkers with another person\n"
                "  3. Quit\n"
                "Enter a number to choose: ";

  std::cout << welcome << std::endl << menuOptions;
}

void GameUI::InvalidInputMessage() {
  std::cerr << "\n\033[31mERROR\033[0m: Invalid input provided" << std::endl;
}

void GameUI::IllegalMoveMessage() {
  std::cerr << "\n\033[31mERROR\033[0m: Illegal move attempted"  << std::endl;
}

void GameUI::UpdateBoard(bool updateTurn) {
  
  if (updateTurn) {
    turn_number++;
    if(typeid(player1) == typeid(player2)) {
      board_is_flipped_up = not board_is_flipped_up;
    }
  }
  
  bool isLightBoardTile = true; // Top-left and bottom-right are both light
  std::string darkBoardTile = "\033[40m   \033[0m";
  std::string lightBoardTile = "\033[47m   \033[0m";
  std::stringstream output;
  output << "\n\n";
  
  // Header
  if (typeid(player1) == typeid(player2)) {
    output << "CHECKERS: Two-Player Mode        Turn: ";
  } else {
    output << "CHECKERS: Single-Player Mode     Turn: ";
  }
  output << turn_number << "\n";
  
  // Normal board
/*  if (board_is_flipped_up) { */
    output << "    1  2  3  4  5  6  7  8 \n\n";
    for (auto row = 0; row < 8; ++row) {
      output << static_cast<char>('A'+row) << "  ";
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
      output << "\n";

      isLightBoardTile = not isLightBoardTile;
    }
    output << "\n";    
  // Upside Down GameBoard
/*  } else {
    output << "    8  7  6  5  4  3  2  1 \n\n";
    for (auto row = 7; row >= 0; --row) {
      output << static_cast<char>('A'+row) << "  ";
      for (auto column = 7; column >= 0; --column) {
        if (isLightBoardTile) {
          output << lightBoardTile;
        } else if (board->GetPiece(row, column) == nullptr) {
          output << darkBoardTile;
        } else {
          output << *(board->GetPiece(row, column));
        }
        isLightBoardTile = not isLightBoardTile;
      }
      output << "\n";

      isLightBoardTile = not isLightBoardTile;
    }
  }
  output << "\n";*/
  
  // Footer
  output << "Enter a sequence of coordinates to move a piece\n"
         << "  e.g., 'F1 D4 B1' would be a double jump\n";
  if (turn_number % 2 == 1)
    output << "Player One's Move: ";
  else
    output << "Player Two's Move: ";
  
  std::cout << output.str();
}

void GameUI::EndGame(bool player1_wins) {
  std::stringstream output;
  
  output << " ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██╗   ██╗███████╗██████╗ ██╗\n"
         << "██╔════╝ ██╔══██╗████╗ ████║██╔════╝   ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║\n"
         << "██║  ███╗███████║██╔████╔██║█████╗     ██║   ██║██║   ██║█████╗  ██████╔╝██║\n"
         << "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝     ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝\n"
         << "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗\n"
         << " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝\n"
         << std::endl;
  
  if ( player1_wins )
    output << "Player 1 Wins, ";
  else
    output << "Player 2 Wins, ";
  
  output << "Congratulations!!!\n";
  output << "Would you like to play again? (y or n): ";
  std::cout << output.str();
}
