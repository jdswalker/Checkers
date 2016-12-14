// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c Piece.cc -o Piece.o

#include <iostream>
#include <string>

#include "Colour.h"
#include "Piece.h"
#include "PieceType.h"

// PUBLIC METHODS
// Constructor for normal pieces
Piece::Piece(Colour newColour) {
  colour = newColour;
  type = PieceType::NORMAL;
}

// Constructor for any game piece
Piece::Piece(PieceType newType, Colour newColour) {
  colour = newColour;
  type = newType;
}

// Destructor
Piece::~Piece() {};

// Returns the colour of the piece
Colour Piece::GetColour() const {
  return colour;
}

// Returns the type of the piece (i.e., normal or king)
PieceType Piece::GetType() const {
  return type;
}

// Changes the type of game piece (e.g., normal => king)
void Piece::SetType(PieceType newType) {
  type = newType;
}

// Overloaded stream operator to allow outputting pieces directly
std::ostream &operator<< (std::ostream& output, const Piece& piece) {
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
  
  return output << token << Piece::RESET_STREAM;
}

// PRIVATE CONSTANTS
// Determines how a Piece object renders when output
const std::string Piece::RED          = "\033[1;31;40m";
const std::string Piece::WHITE        = "\033[1;40m";
const std::string Piece::RESET_STREAM = "\033[0m";
const std::string Piece::NORMAL       = " \u25CF "; //"\u25CF" => filled circle
const std::string Piece::KING         = " \u265B "; //"\u25CB" => hollow circle
