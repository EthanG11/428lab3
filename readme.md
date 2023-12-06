ERRORS:
expression cannot be used as function. I was getting this error because I put a value into the std::find_if function instead of a unary predicate

linker couldnt find definition of destructor for GoFishGameClass because i just put the virtual declaration with no definition

Additions:
added a players vector to the GoFishGame class so that we could easily print the names of the players to cout.
created overloaded findMatch functions, which allowed us to compare user input of a card rank to the real card rank.
added removedPlayers list vector to GoFishGame class, which allowed us to let the game function properly when players were removed.

Trials:

1. HoldEm Deck

2. Uno Deck

3. Pinochle Deck

4. make a book and repeat turn
   PLAYER: a
   7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
   Books:
   PLAYER: b
   8 C 9 C 9 D 9 H K D 2 D  
   Books: 10 H 10 C 10 S 10 D

PLAYER: c
K S J C K H J H 6 H K C J S  
Books: Q H Q C Q S Q D

PLAYER: d
A C 2 H 3 C A S 3 S 3 D 2 S  
Books:
PLAYER: e
8 H A D  
Books:
TURN OF player: c
What card rank and what player number? enter as rank number
king 1
PLAYER: a
7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
Books:
PLAYER: b
8 C 9 C 9 D 9 H 2 D  
Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 2 H 3 C A S 3 S 3 D 2 S  
Books:
PLAYER: e
8 H A D  
Books:
TURN OF player: c
What card rank and what player number? enter as rank number

5. count rounds and end game with winning player(s)
   TURN OF player: c
   What card rank and what player number? enter as rank number SPACE player number
   five 3
   player: 2 removed from game
   book count: player: a: 3
   player: b: 4
   player: c: 1
   player: d: 0
   player: e: 5
   round number: 6
   game over. player(s) w/ most books:
   4 , winning book count: 5

6. go fish draw from deck works when player doesn't have target card
   PLAYER: a
   7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
   Books:
   PLAYER: b
   9 C 9 D 9 H  
   Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 3 C A S 3 S 3 D J D  
Books: 2 H 2 S 2 C 2 D

PLAYER: e
8 H A D 8 C 8 S  
Books:
TURN OF player: e
What card rank and what player number? enter as rank number
eight 0
Go fish
book count: player: a: 0
player: b: 1
player: c: 2
player: d: 1
player: e: 0
round number: 3
PLAYER: a
7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
Books:
PLAYER: b
9 C 9 D 9 H  
Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 3 C A S 3 S 3 D J D  
Books: 2 H 2 S 2 C 2 D

PLAYER: e
8 H A D 8 C 8 S 3 H  
Books:
TURN OF player: a
What card rank and what player number? enter as rank number

8. repeat turn when card drawn from go fish is target card
   PLAYER: a
   7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
   Books:
   PLAYER: b
   9 C 9 D 9 H  
   Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 3 C A S 3 S 3 D J D  
Books: 2 H 2 S 2 C 2 D

PLAYER: e
8 H A D 8 C  
Books:
TURN OF player: e
What card rank and what player number? enter as rank number
eight 3
Go fish
PLAYER: a
7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
Books:
PLAYER: b
9 C 9 D 9 H  
Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 3 C A S 3 S 3 D J D  
Books: 2 H 2 S 2 C 2 D

PLAYER: e
8 H A D 8 C 8 S  
Books:
TURN OF player: e
What card rank and what player number? enter as rank number

9. draw card on turn when hand is empty
   TURN OF player: d
   What card rank and what player number? enter as rank number
   three 2
   PLAYER: a
   7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H  
   Books:
   PLAYER: b
   8 C 9 C 9 D 9 H K D  
   Books: 10 H 10 C 10 S 10 D

PLAYER: c
K S J C K H J H 6 H K C  
Books: Q H Q C Q S Q D

PLAYER: d
A C 2 H 3 C J S A S 3 S 3 D  
Books:
PLAYER: e

Books:
TURN OF player: d
What card rank and what player number? enter as rank number
three 4
Go fish
PLAYER: a
7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H  
Books:
PLAYER: b
8 C 9 C 9 D 9 H K D  
Books: 10 H 10 C 10 S 10 D

PLAYER: c
K S J C K H J H 6 H K C  
Books: Q H Q C Q S Q D

PLAYER: d
A C 2 H 3 C J S A S 3 S 3 D 2 S  
Books:
PLAYER: e
8 H  
Books:
TURN OF player: e
What card rank and what player number? enter as rank number

10. remove player when deck is empty and cannot draw.

TURN OF player: b
What card rank and what player number? enter as rank number SPACE player number
ace 4
PLAYER: a
A C K H Q C Q H 5 D 7 H Q D  
Books: 3 H 3 C 3 S 3 D  
10 H 10 C 10 S 10 D

PLAYER: b
A D Q S 2 C A H  
Books: 9 C 9 H 9 D 9 S  
4 H 4 C 4 S 4 D

PLAYER: c
6 D K D 5 H A S 5 C 6 H 7 C 6 C  
Books:
PLAYER: d
2 D J D 6 S 2 S J S J C K C 5 S  
Books: 8 D 8 S 8 C 8 H

PLAYER: e
2 H 7 S 7 D K S J H  
Books:
TURN OF player: b
What card rank and what player number? enter as rank number SPACE player number
ace 3
Go fish
player 1 removed from game
PLAYER: a
A C K H Q C Q H 5 D 7 H Q D  
Books: 3 H 3 C 3 S 3 D  
10 H 10 C 10 S 10 D

PLAYER: b

Books: 9 C 9 H 9 D 9 S  
4 H 4 C 4 S 4 D

PLAYER: c
6 D K D 5 H A S 5 C 6 H 7 C 6 C  
Books:
PLAYER: d
2 D J D 6 S 2 S J S J C K C 5 S  
Books: 8 D 8 S 8 C 8 H

PLAYER: e
2 H 7 S 7 D K S J H  
Books:
TURN OF player: c
What card rank and what player number? enter as rank number SPACE player number

"reprompts later in game after player e tries to request from removed player"

TURN OF player: e
What card rank and what player number? enter as rank number SPACE player number
seven 0
PLAYER: a
Q C Q H Q D  
Books: 3 H 3 C 3 S 3 D  
10 H 10 C 10 S 10 D

PLAYER: b

Books: 9 C 9 H 9 D 9 S  
4 H 4 C 4 S 4 D

PLAYER: c
6 D A S 6 H 7 C 6 C A C A D Q S  
Books: K D K S K H K C  
5 H 5 C 5 D 5 S

PLAYER: d
J D 6 S J S J C  
Books: 8 D 8 S 8 C 8 H

PLAYER: e
7 S 7 D J H 7 H  
Books: 2 H 2 D 2 S 2 C

TURN OF player: e
What card rank and what player number? enter as rank number SPACE player number
seven 1
What card rank and what player number? enter as rank number SPACE player number

11. show current score after each round
    What card rank and what player number? enter as rank number
    eight 0
    Go fish
    book count: player: a: 0
    player: b: 1
    player: c: 2
    player: d: 1
    player: e: 0
    round number: 3
    PLAYER: a
    7 H 4 S 5 D 6 C 7 D 5 C 5 S 7 C 4 H 6 S  
    Books:
    PLAYER: b
    9 C 9 D 9 H  
    Books: 10 H 10 C 10 S 10 D

PLAYER: c
J C J H 6 H J S  
Books: Q H Q C Q S Q D  
K S K H K C K D

PLAYER: d
A C 3 C A S 3 S 3 D J D  
Books: 2 H 2 S 2 C 2 D

PLAYER: e
8 H A D 8 C 8 S 3 H  
Books:
TURN OF player: a
What card rank and what player number? enter as rank number
