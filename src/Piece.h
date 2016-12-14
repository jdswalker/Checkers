// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_PIECE_H_
#define CHECKERS_GAME_PIECE_H_

#include <iostream>
#include <string>

#include "Colour.h"
#include "PieceType.h"

class Piece {
 public:
  Piece(PieceType newType, Colour newColour);
  Piece(Colour newColour);
  ~Piece();
  
  Colour GetColour() const;
  PieceType GetType() const;
  void SetType(PieceType type);
  
  friend std::ostream &operator<<(std::ostream& output, const Piece& piece);

 private:
  PieceType type;
  Colour colour;

  static const std::string RED;
  static const std::string WHITE;
  static const std::string RESET_STREAM;

  static const std::string NORMAL;
  static const std::string KING;
};

#endif // CHECKERS_GAME_PIECE_H_
