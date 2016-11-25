// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=c++11 -Wall -Werror -c Move.cc -o Move.o

#include <array>
#include <vector>

#include "Move.h"

Move::Move(std::vector< std::array<int, 2> > newSequence) {
  sequence = newSequence;
}

std::array<int, 2> Move::GetNext() {
  ++cursor;
  return sequence[cursor];
}

bool Move::HasNext() {
  return sequence.size() > cursor+1;
}

std::array<int, 2> Move::GetFirst() {
  cursor = 0;
  return sequence[cursor];
}

int Move::GetLength() {
  return sequence.size();
}
