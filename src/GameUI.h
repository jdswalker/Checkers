//
// Created by colin on 11/11/16.
//

#ifndef CHECKERS_GAMEUI_H
#define CHECKERS_GAMEUI_H

#include <memory>

#include "GameBoard.h"
#include "Player.h"

#include "GameUI.h"

class GameUI {
 public:
  GameUI();
  void InitUI(std::shared_ptr<GameBoard> newBoard, std::shared_ptr<Player> newPlayer1, std::shared_ptr<Player> newPlayer2);
  void MainMenu();

  void InvalidInputMessage();
  void IllegalMoveMessage();
  void UpdateBoard(bool updateTurn);
  void EndGame(bool player1_wins);
  
 private:
  std::shared_ptr<GameBoard> board;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  unsigned int turn_number;
  bool board_is_flipped_up;
};

#endif //CHECKERS_GAMEUI_H
