// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the CardSet template class declaration. This class is inherited by the Deck template class.

#pragma once
#include "card_T.h"
#include <vector>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>

// the set of cards that are only allowed in the deck for a given game type.
template <typename Suit, typename Rank>
class CardSet
{
public:
    typedef Card<Suit, Rank> card_type;
    typedef typename std::vector<Card<Suit, Rank>>::iterator iter;
    typedef Rank rank_type;
    typedef Suit suit_type;

    void print(std::ostream &o, size_t size); // print every card in the set
    CardSet<Suit, Rank> &operator>>(CardSet<Suit, Rank> &set); // use the >> operator to push an equivalent last card onto the set
    bool is_empty(); // check if the set has no cards

    // static std::vector<Card<Suit, Rank>> CardSet<Suit, Rank>::*access_cards();

    typename std::vector<Card<Suit, Rank>>::iterator getBeginIterator();
    typename std::vector<Card<Suit, Rank>>::iterator getEndIterator();
    void sort(); //call std::sort by rank and by suit
    void collect(CardSet<Suit, Rank> &set); // shift all of the cards out of the CardSet and into the Deck
    void collect_if(CardSet<Suit, Rank> &deck, std::function<bool(Card<Suit, Rank> &)> pred); //shift only cards that meet a given criteria
    bool request(CardSet<Suit, Rank> &cardSet, rank_type &rank); //find a card in the provided CardSet matching the provided rank

protected:
    std::vector<Card<Suit, Rank>> cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif
