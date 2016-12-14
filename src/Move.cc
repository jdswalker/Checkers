// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c Move.cc -o Move.o

#include <vector>     // vector
#include <utility>    // pair, make_pair

#include "Move.h"

// Empty Constructor
Move::Move() {
  cursor = -1;
  sequence = {};
}

// Constructor accepting a move sequence
Move::Move(std::vector< std::pair<int,int> > newSequence) {
  cursor = -1;
  sequence = newSequence;
}

// Returns the first move in the sequence of moves
std::pair<int,int> Move::GetFirst() {
  cursor = 0;
  return sequence[cursor];
}

// Returns the next move in the sequence of moves based on the cursor position
std::pair<int,int> Move::GetNext() {
  ++cursor;
  return sequence[cursor];
}

// Checks if there are still additional moves in the sequence
bool Move::HasAnotherMove() {
  return (cursor + 1) < (int)sequence.size();
}

// Returns the move sequence
std::vector< std::pair<int,int> > Move::GetMoveSequence() const {
  return sequence;
}

// Returns the number of moves in the sequence
int Move::GetMoveSequenceLength() {
  return sequence.size();
}

// Equals comparison operator
bool Move::operator==(const Move &otherMoveSequence) const {
  return this->GetMoveSequence() == otherMoveSequence.GetMoveSequence();
}

// Not equals comparison operator
bool Move::operator!=(const Move &otherMoveSequence) const {
  return this->GetMoveSequence() != otherMoveSequence.GetMoveSequence();
}
