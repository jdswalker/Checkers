// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_PLAYER_BASE_CLASS_H_
#define CHECKERS_GAME_PLAYER_BASE_CLASS_H_

#include "Colour.h"
#include "Move.h"

class Player {
 public:
  Player(Colour newColour);
  Colour GetColour();

  virtual bool IsHuman() = 0;
  virtual Move GetMove() = 0;

 private:
  Colour player_colour;
};

#endif // CHECKERS_GAME_PLAYER_BASE_CLASS_H_
