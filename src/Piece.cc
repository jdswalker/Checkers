// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=c++11 -Wall -Werror -c Piece.cc -o Piece.o

#include <iostream>
#include <string>

#include "Colour.h"
#include "PieceType.h"

#include "Piece.h"

// Constructors
Piece::Piece(Colour newColour) {
  colour = newColour;
  type = PieceType::NORMAL;
}

Piece::Piece(PieceType newType, Colour newColour) {
  colour = newColour;
  type = newType;
}

Piece::~Piece() {};

// Mutators
Colour Piece::GetColour() const {
  return colour;
}

PieceType Piece::GetType() const {
  return type;
}

void Piece::SetType(PieceType newType) {
  type = newType;
}

// Overloaded stream operator for output
std::ostream& operator<< (std::ostream& output, const Piece& piece) {
  std::string token;
  switch(piece.GetColour()){
    case Colour::DARK: {
      token = Piece::RED;
      break;
    }
    case Colour::LIGHT: {
      token = Piece::WHITE;
      break;
    }
  }
  
  switch(piece.GetType()){
    case PieceType::NORMAL: {
      token += Piece::NORMAL;
      break;
    }
    case PieceType::KING: {
      token += Piece::KING;
      break;
    }
  }
  
  const std::string RESET_STREAM = "\033[0m";
  
  return output << token << RESET_STREAM;
}

const std::string Piece::WHITE = "\033[1;40m";
const std::string Piece::RED = "\033[1;31;40m";
const std::string Piece::NORMAL = " \u25CF ";
const std::string Piece::KING = " \u25CB ";
