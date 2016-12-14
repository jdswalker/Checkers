// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_MOVE_SEQUENCE_HANDLER_H_
#define CHECKERS_GAME_MOVE_SEQUENCE_HANDLER_H_

#include <vector>     // vector
#include <utility>    // pair, make_pair

class Move {
 public:
  Move();
  Move(std::vector< std::pair<int,int> > newSequence);
  
  std::pair<int,int> GetFirst();
  std::pair<int,int> GetNext();
  bool HasAnotherMove();
  std::vector< std::pair<int,int> > GetMoveSequence() const;
  int GetMoveSequenceLength();
  
  bool operator==(const Move &otherMoveSequence) const;
  bool operator!=(const Move &otherMoveSequence) const;

 private:
  int cursor;
  std::vector< std::pair<int,int> > sequence;
};

#endif // CHECKERS_GAME_MOVE_SEQUENCE_HANDLER_H_
