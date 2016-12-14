// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_PLAYER_ARTIFICIAL_INTELLIGENCE_H_
#define CHECKERS_GAME_PLAYER_ARTIFICIAL_INTELLIGENCE_H_

#include <memory>   // shared_ptr

#include "Colour.h"
#include "GameBoard.h"
#include "Move.h"
#include "Player.h"

class PlayerAI : public Player {
 public:
  // Constructor
  PlayerAI(Colour newColour, std::shared_ptr<GameBoard> newBoard);
  
  // Defined in base class
  // Colour GetColour();

  // Virtual in base class
  bool IsHuman();
  Move GetMove();

 private:
  std::shared_ptr<GameBoard> board_copy;
};

#endif //CHECKERS_GAME_PLAYER_ARTIFICIAL_INTELLIGENCE_H_
