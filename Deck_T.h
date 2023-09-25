// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the abstract deck class which will be inherited by the pinochle and poker classes. They each require the declaration of
// the print statement.

#pragma once
#include "card_T.h"
#include "Suits.h"
#include "CardSet_T.h"
#include <random>
#include <algorithm>

template <typename Suit, typename Rank>
class Deck : public CardSet<Suit, Rank>
{
public:
       void shuffle();
       void collect(CardSet<Suit, Rank> &set);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Deck_T.cpp"
#endif
