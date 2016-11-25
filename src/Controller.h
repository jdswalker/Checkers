//
// Created by colin on 11/10/16.
//

#ifndef CHECKERS_CONTROLLER_H
#define CHECKERS_CONTROLLER_H

#include <memory>

#include "GameBoard.h"
#include "GameError.h"
#include "GameUI.h"
#include "Player.h"

#include "Controller.h"

class Controller {
 public:
  Controller();
  void StartGame();
  void GetValidInput();
  
 private:
  GameMode GetGameMode();
  bool IsLegalMove(Move action);
  void ExecuteMove(Move action);
  bool CheckLose();
  void PauseGame(int time);
  std::string GetInput();
  void ShowError(GameError errorType, int time);
  bool PlayAgain();

  std::shared_ptr<GameBoard> board;
  std::shared_ptr<GameUI> gameUI;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  std::shared_ptr<Player> activePlayer;
};

#endif //CHECKERS_CONTROLLER_H


#ifndef CONTROLLER_GAME_MODE_H
#define CONTROLLER_GAME_MODE_H

enum class GameMode { TWOPLAYER, PLAYERCOMPUTER };

#endif // CONTROLLER_GAME_MODE_H

#ifndef CONTROLLER_GAME_ERROR_H
#define CONTROLLER_GAME_ERROR_H

enum class GameError { INVALID, ILLEGAL };

#endif // CONTROLLER_GAME_ERROR_H
