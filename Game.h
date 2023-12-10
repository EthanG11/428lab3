// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the declaration of the Game class, which all games--Poker, Pinochle, GoFish, and Uno--inherit.
// It sets up general functions required for all games.

#pragma once
#include <vector>
#include <string>
#include <iostream>

class Game
{
public:
    Game(int argc, const char *argv[]);
    virtual int play() = 0;
    bool promptEndGame();
    int SUCCESS = 0;

protected:
    std::vector<std::string> players;
};