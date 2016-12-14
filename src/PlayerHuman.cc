// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror -c PlayerHuman.cc -o PlayerHuman.o

#include <algorithm>  // transform
#include <iostream>   // cin, getline
#include <sstream>    // istringstream
#include <string>     // tolower
#include <vector>     // vector
#include <utility>    // pair

#include "Colour.h"
#include "PlayerHuman.h"
#include "Move.h"
#include "Player.h"

// PUBLIC METHODS
// Constructor
PlayerHuman::PlayerHuman(Colour colour): Player(colour), input("") {}

// This should be the only class that indicates true for this function
bool PlayerHuman::IsHuman(){
  return true;
}

// Parses user input for grid coordinates and builds a sequence of moves
Move PlayerHuman::GetMove() {

  if (not HasValidInput()) {
    return Move();
  }

  std::vector<std::pair<int,int>> sequence;
  auto split_input = Split(input, ' ');
  
  for (auto const& coordinates : split_input) {
    int row = coordinates[0]-'a';
    int column = coordinates[1]-'1';
    sequence.emplace_back(row, column);
  }

  return sequence;
}

// Gets the user's input from std::cin and stores it in the PlayerHuman object
void PlayerHuman::SetInput() {
  std::string newInput;
  std::getline(std::cin, newInput);
  
  // Turns all input to lowercase
  std::transform(newInput.begin(), newInput.end(), newInput.begin(), ::tolower);
  
  input = newInput;
}

// Retrieves the input stored by the PlayerHuman object
std::string PlayerHuman::GetInput() {
  return input;
}

// Checks whether the input stored by the PlayerHuman object is a valid set of
// coordinates or a recognized command
bool PlayerHuman::HasValidInput() {
  if (input.length() < 2) {
    return false;
  }
  
  if (   input == "q"
      or input == "quit"
      or input == "exit") {
    return true;
  }
  
  std::vector<std::string> split_input = Split(input, ' ');
  if (split_input.size() < 2) {
    return false;
  }
  
  for (auto const& coordinates : split_input) {

    if (not ((coordinates.length() == 2)
             and (0 <= (coordinates[0]-'a'))
             and (7 >= (coordinates[0]-'a'))
             and (0 <= (coordinates[1]-'1'))
             and (7 >= (coordinates[1]-'1')) )) {

      return false;
    }
  }
  
  return true;
}

// PRIVATE METHODS
// Parses the input string sequence into individual sets of coordinates
std::vector<std::string> PlayerHuman::Split(std::string input, char delim) {

  std::istringstream inputSequence(input);
  std::string newInput;
  std::vector<std::string> elements;
  
  while (std::getline(inputSequence, newInput, delim)) {
    elements.emplace_back(newInput);
  }
  
  return elements;
}
