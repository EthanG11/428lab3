#pragma once

#include <iostream>
#include "Deck_T.h"
enum class Color
{
    red,
    blue,
    green,
    yellow,
    black,
    undefined
};

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

class UnoDeck : public Deck<Color, UnoRank>
{
public:
    UnoDeck();
};

std::ostream &
operator<<(std::ostream &, UnoRank &);
UnoRank operator++(UnoRank &r);

std::ostream &operator<<(std::ostream &, Color &);
Color operator++(Color &c);
