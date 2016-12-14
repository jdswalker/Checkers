// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c Player.cc -o Player.o

#include "Colour.h"
#include "Player.h"

// PUBLIC METHODS
// Constructor
Player::Player(Colour newColour) {
  player_colour = newColour;
}

// Returns the colour of game piece used by the player
Colour Player::GetColour() {
  return player_colour;
}
