# CSCI 3132 - Object-oriented Text-based UI Checkers  
Authors: <a href="https://github.com/ColinVDH/">Colin Vandenhof</a> 
& <a href="https://github.com/JDSWalker/">James Walker</a>  
©2016 under the [MIT license](www.opensource.org/licenses/mit-license.php)

## Overview  

#### Motivation:
This C++ program was developed as part of a group project for CSCI 3132, <a href="http://academiccalendar.dal.ca/Catalog/ViewCatalog.aspx?pageid=viewcatalog&topicgroupid=10330&entitytype=CID&entitycode=CSCI+3132">Object-orientation and Generic Programming</a>. The goal of the project was to implement a game with a text-based user interface and show some of the object-oriented concepts learned throughout the course. To this end, my group implemented the popular <a href="https://en.wikipedia.org/wiki/English_draughts">English Checkers</a> version of the game.

#### Program Status & Issues:
- [x] Implement two-player mode
- [ ] Implement one-player mode (i.e., add computer player)
- [ ] Add check to ensure player enters the move sequence that maximizes the number of jumps (if jump moves are available; required by game rule)

#### Required Tools:  
- make   
- g++  
- Unix-based console that supports ANSI and Unicode  

#### Compilation and Program Execution:  
<pre>$ make
$ ./Checkers.exe</pre>  
  
#### Screenshot from Checkers Program Running in Cygwin Terminal:  

<img src="./img/CheckerThisOut.png" title="Screenshot from Checkers Program" alt="Checkers Screenshot" height="1050" width="801"/>  

#### A Complete Checkers Game:

<img src="./img/CheckersGamePlay.gif" title="Animated Game Play from Checkers Program" alt="Animated Game Play from Checkers Program" height="356" width="666"/>  

| <div>Turn</div><div>(Player)</div> | <div>Formal</div><div>Notation</div> | <div>Move</div><div>Sequence</div> | <div>Effect</div> |
|:-----------:|:--------:|:-----------:|:--------------------------------|
|  1 (Red)    | 11-16    | C6 D7       |                                 |
|  2 (White)  | 21-17    | F1 E2       |                                 |
|  3 (Red)    | 10-14    | C4 D3       |                                 |
|  4 (White)  | 17×10    | E2 C4       |_Player 1 (Red) Loses Piece_     |
|  5 (Red)    | 6×15     | B3 D5       |_Player 2 (White) Loses Piece_   |
|  6 (White)  | 23-18    | F5 E4       |                                 |
|  7 (Red)    | 2-6      | A4 B3       |                                 |
|  8 (White)  | 18×2     | E4 C6 A4    |_Player 1 (Red) Loses 2 Pieces_  |
|  9 (Red)    | 9-14     | C2 D3       |                                 |
| 10 (White)  | 2×18     | A4 C2 E4    |_Player 1 (Red) Loses 2 Pieces_  |
| 11 (Red)    | 3-7      | A6 B5       |                                 |
| 12 (White)  | 24-20    | F7 E8       |                                 |
| 13 (Red)    | 1-6      | A2 B3       |                                 |
| 14 (White)  | 20×2     | E8 C6 A4    |_Player 1 (Red) Loses 2 Pieces_  |
| 15 (Red)    | 12-16    | C8 D7       |                                 |
| 16 (White)  | 2×9      | A4 C2       |_Player 1 (Red) Loses Piece_     |
| 17 (Red)    | 5×23     | B1 D3 F5    |_Player 2 (White) Loses 2 Pieces_|
| 18 (White)  | 26×3     | G4 E6 C8 A6 |_Player 1 (Red) Loses 3 Pieces_  |
| 19 (Red)    | 4-8      | A8 B7       |                                 |
| 20 (White)  | 3×12     | A6 C8       |_Player 1 (Red) Loses Piece_     |
|**Game Over**| ***-***  | ***-***     |**_Player 2 (White) wins_**      |
