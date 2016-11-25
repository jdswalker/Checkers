// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_MOVE_H
#define CHECKERS_MOVE_H

#include <string>
#include <vector>
#include <array>

class Move {
 public:
  Move(std::vector< std::array<int, 2> > newSequence);
  bool HasNext();
  std::array<int, 2> GetFirst();
  std::array<int, 2> GetNext();
  int GetLength();

 private:
  std::vector< std::array<int, 2> > sequence;
  unsigned int cursor = 0;
};

#endif // CHECKERS_MOVE_H
