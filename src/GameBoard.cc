// Authors: @ColinVDH and @JDSWalker
// Created on: 11/10/16
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=colour++11 -Wall -Werror -colour GameBoard.cc -o GameBoard.o

#include <array>      // array
#include <cmath>      // abs()
#include <memory>     // shared_ptr<>(), make_shared<>()
#include <string>     // string
#include <iostream>

#include "Colour.h"
#include "PieceType.h"
#include "Piece.h"
#include "GameBoard.h"

// CONSTRUCTOR
GameBoard::GameBoard() {
  darkPieces = 12;
  lightPieces = 12;
  
  // Setup red game pieces
  for (auto row = 0; row < 3; ++row) {
    bool placePiece = row % 2 != 0;
    for (auto column = 0; column < 8; ++column) {
      board[row][column] = placePiece ? std::make_shared<Piece>(Piece(Colour::DARK)) : nullptr;
      placePiece = !placePiece;
    }
  }
  
  // Setup empty middle with null pointers
  for (auto row = 4; row < 5; ++row) {
    for (auto column = 0; column < 8; ++column) {
      board[row][column] = nullptr;
    }
  }
  
  // Setup white game pieces
  for (auto row = 5; row < 8; ++row) {
    bool placePiece = row % 2 != 0;
    for (auto column = 0; column < 8; ++column) {
      board[row][column] = placePiece ? std::make_shared<Piece>(Piece(Colour::LIGHT)) : nullptr;
      placePiece = !placePiece;
    }
  }
}

// DESTRUCTOR
GameBoard::~GameBoard() {
  for(auto row : board) {
    for (auto gridSpot : row){
      gridSpot = nullptr;
    }
  }
}

std::shared_ptr<Piece> GameBoard::GetPiece(int row, int column) {
  if(row < 0 or row > 7 or column < 0 or column > 7)
    return nullptr;
  return board[row][column];
}

std::shared_ptr<Piece> GameBoard::GetPiece(std::array<int, 2> gridSpot) {
  return GetPiece( gridSpot[0], gridSpot[1] );
}

bool GameBoard::IsLegalJump(std::shared_ptr<Piece> piece,
                            std::array<int, 2> fromTile,
                            std::array<int, 2> toTile) {

  if (piece == nullptr or (not WithinBounds(toTile)) or (GetPiece(toTile) != nullptr)) {
    return false;
  }

  if (piece->GetType() == PieceType::KING
      or piece->GetColour() == Colour::LIGHT) {
    if ((toTile[0]-fromTile[0] == -2) and (std::abs(toTile[1]-fromTile[1]) == 2)) {
      auto jumped = GetPiece((toTile[0]+1), (toTile[1]+fromTile[1])/2);
      if(jumped == nullptr)
        return false;
      if(jumped->GetColour() == piece->GetColour())
        return false;
      return true;
    }
  }
  
  if (piece->GetType() == PieceType::KING
      or piece->GetColour() == Colour::DARK) {
    if ((toTile[0]-fromTile[0] == 2) and (std::abs(toTile[1]-fromTile[1]) == 2)) {
      auto jumped = GetPiece((toTile[0]-1), (toTile[1]+fromTile[1])/2);
      if(jumped == nullptr)
        return false;
      if(jumped->GetColour() == piece->GetColour())
        return false;
      return true;
    }
  }
  return false;
}

bool GameBoard::IsLegalSlide(std::array<int, 2> fromTile,
                             std::array<int, 2> toTile) {
  auto piece = GetPiece(fromTile);
  if (piece == nullptr or not WithinBounds(toTile)) {
    return false;
  }
  
  auto colour = piece->GetColour();
  if ( GetPiece(toTile) != nullptr ){
    return false;
  }

  auto type = piece->GetType();
  if (type == PieceType::KING or colour == Colour::LIGHT) {
    if (toTile[0]-fromTile[0] == -1 and std::abs(toTile[1]-fromTile[1]) == 1){
      return true;
    }
  }
  if (type == PieceType::KING or colour == Colour::DARK) {
    if (toTile[0]-fromTile[0] == 1 and std::abs(toTile[1]-fromTile[1]) == 1){
      return true;
    }
  }
  return false;
}

bool GameBoard::JumpsAvailable(Colour colour) {
  for (auto row = 0; row < 8; ++row) {
    for (auto column = 0; column < 8; ++column) {
      auto piece = board[row][column];
      if (piece == nullptr or piece->GetColour() != colour) {
        continue;
      }
      if (piece->GetType() == PieceType::KING or colour == Colour::LIGHT) {
        if (IsLegalJump( piece, {row, column}, {row-2, column+2} ) or
            IsLegalJump( piece, {row, column}, {row-2, column-2} )) {    
          return true;
        }
      }
      if (piece->GetType() == PieceType::KING or colour == Colour::DARK) {
        if (IsLegalJump( piece, {row, column}, {row+2, column+2} ) or
            IsLegalJump( piece, {row, column}, {row+2, column-2} )) {    
          return true;
        }
      }
    }
  }
  return false;
}

bool GameBoard::PiecesRemaining(Colour colour) {
  return (colour == Colour::DARK) ? (darkPieces > 0) : (lightPieces > 0);
}

bool GameBoard::MovesRemaining(Colour colour) {
  bool result = false;
  for (auto row = 0; row < 8; row++){
    for (auto column = 0; column < 8; ++column){
      auto piece = GetPiece(row, column);
      
      if (piece == nullptr || piece->GetColour() != colour)
        continue;

      if (piece->GetType() == PieceType::KING or colour == Colour::LIGHT) {
        if (IsLegalJump( piece, {row, column}, {row-2, column+2} ) or
            IsLegalJump( piece, {row, column}, {row-2, column-2} ) or
            IsLegalSlide( {row, column}, {row-1, column+1} ) or
            IsLegalSlide( {row, column}, {row-1, column-1} ))
          result = true;
      }
      
      if (piece->GetType() == PieceType::KING or colour == Colour::DARK) {
        if (IsLegalJump( piece, {row, column}, {row+2, column+2} ) or
            IsLegalJump( piece, {row, column}, {row+2, column-2} ) or
            IsLegalSlide( {row, column}, {row+1, column+1} ) or
            IsLegalSlide( {row, column}, {row+1, column-1} ))
          result = true;
      }
    }
  }
  return result;
}

void GameBoard::RemovePiece(std::array<int, 2> gridSpot) {
  if (GetPiece(gridSpot)->GetColour() == Colour::LIGHT)
    lightPieces -= 1;
  if (GetPiece(gridSpot)->GetColour() == Colour::DARK)
    darkPieces -= 1;
  
  board[ gridSpot[0] ][ gridSpot[1] ] = nullptr;
}

void GameBoard::MovePiece(std::array<int, 2> fromTile, std::array<int, 2> toTile) {
  board[ toTile[0] ][ toTile[1] ] = std::make_shared<Piece>(*(GetPiece(fromTile)));
  board[ fromTile[0] ][ fromTile[1] ] = nullptr;
    
  if (toTile[0] == 0 and GetPiece(toTile)->GetColour() == Colour::LIGHT)
    GetPiece(toTile)->SetType(PieceType::KING);
  if (toTile[0] == 7 and GetPiece(toTile)->GetColour() == Colour::DARK)
    GetPiece(toTile)->SetType(PieceType::KING);
}

bool GameBoard::IsEmpty(std::array<int,2> gridSpot) {
  return board[ gridSpot[0] ][ gridSpot[1] ] == nullptr;
}

bool GameBoard::WithinBounds(std::array<int, 2> gridSpot) {
  int lowerBound = 0;
  int upperBound = 7;
  
  bool isValidLow = (gridSpot[0] >= lowerBound) and (gridSpot[1] >= lowerBound);
  bool isValidUp =  (gridSpot[0] <= upperBound) and (gridSpot[1] <= upperBound);

  return isValidLow and isValidUp;
}