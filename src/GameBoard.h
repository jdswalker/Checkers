// Authors: @ColinVDH and @JDSWalker
// Created on: 11/10/16
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <array>
#include <string>

#include "Piece.h"

class GameBoard {

public:
  GameBoard();
  ~GameBoard();
  std::shared_ptr<Piece> GetPiece(int x, int y);
  std::shared_ptr<Piece> GetPiece(std::array<int,2> gridSpot);
  bool IsEmpty(std::array<int,2> gridSpot);

  bool IsLegalJump(std::shared_ptr<Piece> piece, std::array<int, 2> fromTile, std::array<int, 2> toTile);
  bool IsLegalSlide(std::array<int,2> fromTile, std::array<int,2> toTile);
  bool JumpsAvailable(Colour c);

  bool PiecesRemaining(Colour c);
  bool MovesRemaining(Colour c);

  void RemovePiece(std::array<int, 2> gridSpot);
  void MovePiece(std::array<int,2> fromTile, std::array<int,2> toTile);

  bool WithinBounds(std::array<int, 2> gridSpot);

 private:
  int darkPieces;
  int lightPieces;
  std::array<std::array<std::shared_ptr<Piece>, 8>, 8> board;
};

#endif //CHECKERS_BOARD_H
