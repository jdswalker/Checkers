// Authors: @ColinVDH and @JDSWalker
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c PlayerAI.cc -o PlayerAI.o

#include <memory>   // shared_ptr
#include <random>   // mt19937, random_device, uniform_int_distribution
#include <vector>   // vector

#include "Colour.h"
#include "PlayerAI.h"
#include "GameBoard.h"
#include "Move.h"
#include "Player.h"

// Constructor
PlayerAI::PlayerAI(Colour colour, 
    std::shared_ptr<GameBoard> newBoard)
    : Player(colour)
    , board_copy(newBoard) {}

// This should always return false since it is not the PlayerHuman class
bool PlayerAI::IsHuman() {
  return false;
}

// Gets the valid set of move sequences for the PlayerAI and chooses a
// move at random (this is not a smart AI, but there are usually only a small
// number of valid move sequences at any given points in time)
Move PlayerAI::GetMove() {
  
  // Get all possible moves
  std::vector<Move> allValidMoves = board_copy->GetAllValidMoves(GetColour());
  
  // 32-bit Mersenne Twister Random Number Generator
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(0, allValidMoves.size()-1);

  return allValidMoves.at(distribution(generator));
}
