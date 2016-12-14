// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_USER_INTERFACE_H_
#define CHECKERS_GAME_USER_INTERFACE_H_

#include <memory>       // shared_ptr

#include "GameBoard.h"
#include "GameError.h"
#include "GameUI.h"
#include "Player.h"

class GameUI {
 public:
  GameUI();
  
  void InitUI(std::shared_ptr<GameBoard> newBoard,
              std::shared_ptr<Player> newPlayer1,
              std::shared_ptr<Player> newPlayer2);
      
  void OutputMainMenu();
  void OutputGameBoard(bool updateTurn);
  void OutputGameOver(bool player1_wins);
  void OutputQuitProgram();
  
  void OutputErrorMessage(GameError errorType);

 private:
  std::shared_ptr<GameBoard> board;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  int turn_number;
};

#endif // CHECKERS_GAME_USER_INTERFACE_H_
