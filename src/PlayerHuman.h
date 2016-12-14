// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_PLAYER_HUMAN_USER_H_
#define CHECKERS_GAME_PLAYER_HUMAN_USER_H_

#include <string>     // string
#include <vector>     // vector

#include "Colour.h"
#include "Move.h"
#include "Player.h"

class PlayerHuman : public Player {
 public:
  // Constructor
  PlayerHuman(Colour colour);
  
  // Defined in base class
  // Colour GetColour();

  // Virtual in base class
  bool IsHuman();
  Move GetMove();

  // Defined in this derived class
  void SetInput();
  std::string GetInput();
  bool HasValidInput();

 private:
  std::vector<std::string> Split(std::string line, char delim);
  
  std::string input;
};

#endif // CHECKERS_GAME_PLAYER_HUMAN_USER_H_
