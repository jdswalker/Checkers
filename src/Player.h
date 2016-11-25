// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include <string>

#include "Colour.h"
#include "Move.h"

class Player {
 public:
  Player(Colour newColour);
  Colour GetColour();
  virtual Move GetMove() = 0;
  virtual bool IsHuman() = 0;
  virtual std::string GetInput() = 0;
  virtual void SetInput() = 0;
  virtual bool HasValidInput() = 0;

  private:
  Colour player_colour;
};

#endif // CHECKERS_PLAYER_H