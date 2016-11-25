// Authors: @ColinVDH and @JDSWalker
// Created on: November 10, 2016
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation: g++ -std=c++11 -Wall -Werror -c HumanPlayer.cc -o HumanPlayer.o

#include <algorithm>  // transform
#include <array>      // array
#include <iostream>   // cin, getline
#include <sstream>    // stringstream
#include <string>
#include <vector>

#include "Colour.h"
#include "Move.h"
#include "Player.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Colour colour): Player(colour) {
  input = "";
}

std::string HumanPlayer::GetInput() {
  return input;
}

void HumanPlayer::SetInput() {
  std::string newInput;
  std::getline(std::cin, newInput);
  std::transform(newInput.begin(), newInput.end(), newInput.begin(), ::tolower);
  input = newInput;
}

bool HumanPlayer::HasValidInput() {
  if (input.length() < 2)
    return false;
  if (input == "q" or input == "quit" or input == "exit")
    return true;
  
  std::vector<std::string> split_input = Split(input, ' ');
  if (split_input.size() < 2)
    return false;
  
  for (auto const& item : split_input) {
    if ( not ( (item.length() == 2) and
               (0 <= (item[0]-'a')) and
               (7 >= (item[0]-'a')) and
               (0 <= (item[1]-'1')) and
               (7 >= (item[1]-'1')) )) {
      return false;
    }
  }
  
  return true;
}

Move HumanPlayer::GetMove() {
  if ( not HasValidInput() ) {
    return Move( {} );
  }

  std::vector< std::array<int, 2> > sequence;
  auto split_input = Split(input, ' ');
  
  for (auto const& item : split_input) {
    int x = item[0]-'a';
    int y = item[1]-'1';
    sequence.push_back({x,y});
  }

  return sequence;
}

std::vector<std::string> HumanPlayer::Split(std::string line, char delim) {
  std::stringstream strStream;
  strStream.str(line);
  
  std::string newInput;
  std::vector<std::string> elements = {};
  
  while (std::getline(strStream, newInput, delim)) {
    std::transform(newInput.begin(), newInput.end(), newInput.begin(), ::tolower);
    elements.emplace_back(newInput);
  }
  
  return elements;
}

bool HumanPlayer::IsHuman(){
  return true;
}
