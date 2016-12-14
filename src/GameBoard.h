// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php

#ifndef CHECKERS_GAME_BOARD_H_
#define CHECKERS_GAME_BOARD_H_

#include <memory>     // shared_ptr, make_shared
#include <vector>     // vector
#include <utility>    // pair

#include "Colour.h"
#include "Move.h"
#include "Piece.h"

class GameBoard {
 public:
  GameBoard();
  GameBoard(GameBoard *obj);
  GameBoard(const GameBoard &obj);
  ~GameBoard();
  
  std::shared_ptr<Piece> GetPiece(int row, int column) const;
  std::shared_ptr<Piece> GetPiece(std::pair<int,int> gridSpot) const;
  bool IsEmpty(std::pair<int,int> gridSpot);

  bool WithinBounds(std::pair<int,int> gridSpot);
  void MovePiece(std::pair<int,int> fromTile, std::pair<int,int> toTile);
  void RemovePiece(std::pair<int,int> gridSpot);

  bool PiecesRemaining(Colour colour);
  bool MovesRemaining(Colour colour);

  bool IsLegalSlide(std::shared_ptr<Piece> piece,
                    std::pair<int,int> fromTile,
                    std::pair<int,int> toTile);
  bool IsLegalJump(std::shared_ptr<Piece> piece,
                   std::pair<int,int> fromTile,
                   std::pair<int,int> toTile);
  bool JumpsAvailable(Colour colour);
  void GetMultiJumps(std::shared_ptr<Piece> piece,
                     std::vector<std::pair<int,int>> seedSequence,
                     std::vector<Move> &allValidMoves);
  std::vector<Move> GetAllValidMoves(Colour colour);
  
  GameBoard &operator=(GameBoard newBoard);

 private:
  bool HasNoRepeatMoves(std::vector<std::pair<int,int>> &sequence,
                        std::pair<int,int> &finish);

  int darkPieces;
  int lightPieces;
  std::array<std::array<std::shared_ptr<Piece>, 8>, 8> board;
};

#endif // CHECKERS_GAME_BOARD_H_
