// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=c++11 -Wall -Werror -c Player.cc -o Player.o

#include "Colour.h"
#include "Player.h"

Player::Player(Colour newColour) {
  player_colour = newColour;
}

Colour Player::GetColour(){
  return player_colour;
}
