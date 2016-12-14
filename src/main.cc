// Authors: @JDSWalker and @ColinVDH
// Copyrighted 2016 under the MIT license:
//   http://www.opensource.org/licenses/mit-license.php
// Compilation:
//   g++ -std=c++11 -Wall -Werror main.cc -o main

#include "Controller.h"

int main() {
    Controller control = Controller();
    control.StartGame();
    return 0;
}
