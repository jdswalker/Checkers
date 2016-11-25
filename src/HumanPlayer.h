// Authors: @ColinVDH and @JDSWalker
// Created on: 11/10/16
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_HUMANPLAYER_H
#define CHECKERS_HUMANPLAYER_H

#include <string>
#include <vector>

#include "Colour.h"
#include "Move.h"
#include "Player.h"

class HumanPlayer : public Player{
 public:
  HumanPlayer(Colour colour);
  Move GetMove();
  bool HasValidInput();
  void SetInput();
  std::string GetInput();
  bool IsHuman();

 private:
  std::string input;
  std::vector<std::string> Split(std::string s, char delim);
};

#endif //CHECKERS_HUMANPLAYER_H