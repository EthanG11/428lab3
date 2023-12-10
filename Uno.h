// Sarah Wilkinson, s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the UnoDeck class, which inherits the Deck template class.
// This class uses its own rank type and has its own rules about how to assemble its game deck.
// It also provides functions to increment and print this specific rank type.

#pragma once

#include <iostream>
#include "Deck_T.h"

//color enum type for uno game
enum class Color
{
    red,
    blue,
    green,
    yellow,
    black,
    undefined
};

//rank type for uno cards
enum class UnoRank
{
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    skip,
    reverse,
    drawtwo,
    drawfour,
    wild,
    blank,
    undefined
};

// a deck for playing uno. contains the cards specific to an uno game.
class UnoDeck : public Deck<Color, UnoRank>
{
public:
    UnoDeck();
};

//how to print and increment uno rank type
std::ostream &operator<<(std::ostream &, UnoRank &);
UnoRank operator++(UnoRank &r);

//how to print and increment the color type
std::ostream &operator<<(std::ostream &, Color &);
Color operator++(Color &c);
