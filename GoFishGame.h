#pragma once

#include "Suits.h"
#include "poker.h"
#include "Game.h"
#include <string>

template <typename Suit = Suit, typename Rank = pokerRank, typename Deck = pokerDeck>
class GoFishGame : public Game
{
    // TODO
    //  static_assert(Deck)
    // static_assert(std::is_base_of_v<CardSet<Suit, Rank>, Deck> == true);

protected:
    Deck deck;

    std::vector<std::string> players;
    std::vector<CardSet<Suit, Rank>> hands;
    std::vector<CardSet<Suit, Rank>> books;
    std::vector<int> removedPlayerList;
    virtual void deal();
    bool turn(int playerNumber);

public:
    GoFishGame(int numPlayers, const char *playerNames[]);
    int numPlayers;
    virtual ~GoFishGame(){};
    virtual int play();
    bool collect_books(int playerNumber);
    const char *playerNames[];
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "GoFishGame.cpp"
#endif