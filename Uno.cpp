// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the function definitions for the UnoDeck class, as well as << and ++ overloads for uno rank and color enum types.

#include "Uno.h"

//initialize an uno deck by assembling the proper uno deck
UnoDeck::UnoDeck()
{
    // populate rank zeroes
    for (int i = 0; i < 4; i++)
    {
        Color color = Color::red;
        Card<Color, UnoRank> zero = Card<Color, UnoRank>(color, UnoRank::zero);
        cards.push_back(zero);
        ++color;
    }

    // poplate one through drawtwo
    Color color = Color::red;
    while (color != Color::black)
    {
        UnoRank rank = UnoRank::one;
        while (rank != UnoRank::drawfour)
        {
            for (int i = 0; i < 2; i++)
            {
                Card<Color, UnoRank> card = Card<Color, UnoRank>(color, rank);
                cards.push_back(card);
            }
            ++rank;
        }
        ++color;
    }

    // black cards
    UnoRank rank = UnoRank::drawfour;

    while (rank != UnoRank::undefined)
    {
        for (int i = 0; i < 4; i++)
        {
            Card<Color, UnoRank> card = Card<Color, UnoRank>(Color::black, rank);
            cards.push_back(card);
        }
        ++rank;
    }
}

// print correct descriptive string for cards of rank type uno.
std::ostream &operator<<(std::ostream &o, UnoRank &rank)
{
    switch (rank)
    {
    case UnoRank::zero:
        o << "zero";
        break;
    case UnoRank::one:
        o << "one";
        break;
    case UnoRank::two:
        o << "two";
        break;
    case UnoRank::three:
        o << "three";
        break;
    case UnoRank::four:
        o << "four";
        break;
    case UnoRank::five:
        o << "five";
        break;
    case UnoRank::six:
        o << "six";
        break;
    case UnoRank::seven:
        o << "seven";
        break;
    case UnoRank::eight:
        o << "eight";
        break;
    case UnoRank::nine:
        o << "nine";
        break;
    case UnoRank::skip:
        o << "skip";
        break;
    case UnoRank::reverse:
        o << "reverse";
        break;
    case UnoRank::drawtwo:
        o << "draw two";
        break;
    case UnoRank::drawfour:
        o << "draw four";
        break;
    case UnoRank::wild:
        o << "wild";
        break;
    case UnoRank::blank:
        o << "blank";
        break;
    case UnoRank::undefined:
        o << "undefined";
        break;
    }
    return o;
}

// increment rank according to uno rank rules.  If it is already the highest rank, then increment it into undefined.
UnoRank operator++(UnoRank &rank)
{
    rank = (rank == UnoRank::undefined) ? rank : (UnoRank)((int)rank + 1);

    return rank;
}

std::ostream &operator<<(std::ostream &o, Color &color)
{
    switch (color)
    {
    case Color::red:
        o << "red";
        break;
    case Color::blue:
        o << "blue";
        break;
    case Color::green:
        o << "green";
        break;
    case Color::yellow:
        o << "yellow";
        break;
    case Color::black:
        o << "black";
        break;
    case Color::undefined:
        o << "undefined";
        break;
    }
    return o;
}

// increment rank according to uno color rules.  If it is already the highest color, then increment it into undefined.
Color operator++(Color &color)
{

    color = (color == Color::undefined) ? color : (Color)((int)color + 1);

    return color;
}
