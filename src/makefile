## Authors: @ColinVDH and @JDSWalker
## Created on: November 10, 2016
## Copyrighted 2016 under the MIT license:
##   http://www.opensource.org/licenses/mit-license.php

# Targets & general dependencies
PROGRAM = Checkers
HEADERS = Colour.h PieceType.h Move.h Piece.h \
          Player.h HumanPlayer.h \
          GameError.h GameMode.h GameBoard.h GameUI.h \
					Controller.h
OBJECTS = Move.o Piece.o \
          Player.o HumanPlayer.o \
          GameBoard.o GameUI.o \
					Controller.o
          
## Compilers, linkers, utilities, and flags
CC = g++
STD = -std=c++11
SRCTYPE = cc
CFLAGS = -Wall -Werror -g

## Creates all .o files, the the program, then removes all .o files
all: $(OBJECTS) $(PROGRAM)
#	rm -f *.o

## Compiles program start point
main.o: main.$(SRCTYPE)
	$(CC) $(STD) -c main.$(SRCTYPE) -o $(PROGRAM).o

$(PROGRAM).o: main.$(SRCTYPE)
	make main.o

## Implicit rule to build .o from .c files
%.o: %.$(SRCTYPE) $(HEADERS)
	$(CC) -c -o $@ $(STD) $(CFLAGS) $<

## Implicit rule to build an executable file from .o files
$(PROGRAM): $(OBJECTS) $(PROGRAM).o
	$(CC) -o $@ $^ $(STD) $(CFLAGS)

## Prevents makefile from trying to compile or handle any file named clean
.PHONY: clean

clean:
	rm -f *.o $(PROGRAM)
	
zip:
	make clean
	rm -f $(PROGRAM).zip
	zip $(PROGRAM).zip *
