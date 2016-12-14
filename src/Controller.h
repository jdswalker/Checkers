// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_PLAY_CONTROLLER_H_
#define CHECKERS_GAME_PLAY_CONTROLLER_H_

#include <memory>     // shared_ptr, make_shared, dynamic_pointer_cast

#include "GameBoard.h"
#include "GameError.h"
#include "GameMode.h"
#include "GameUI.h"
#include "Player.h"

#include "Controller.h"

class Controller {
 public:
  Controller();
  void StartGame();
  
 private:
  GameMode GetGameMode();
  void GetValidInput();
  std::string GetInput();
  
  bool IsLegalMove(Move play);
  void ExecuteMove(Move play);
  
  bool GameHasMoreTurns();
  bool PlayAgain();

  std::shared_ptr<GameBoard> board;
  std::shared_ptr<GameUI> gameUI;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  std::shared_ptr<Player> activePlayer;
};

#endif //CHECKERS_GAME_PLAY_CONTROLLER_H_
