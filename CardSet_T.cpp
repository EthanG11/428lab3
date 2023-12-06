// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the member functions of the CardSet_T template class.
// print(), operator>>(), is_empty(), and access_cards()

#include "CardSet_T.h"

// print every card in the set
template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::print(std::ostream &o, size_t cardsPerLine)
{

    size_t counter = 0;

    for (typename std::vector<Card<Suit, Rank>>::iterator i = cards.begin(); i != cards.end(); i++)
    {

        o << (*i).rank << (*i).suit << " ";
        counter++;

        if (counter == cardsPerLine)
        {
            o << std::endl;
            counter = 0; // reset the counter because card limit per line has been reached
        }
    }
}

// use the >> operator to push an equivalent last card onto the set
template <typename Suit, typename Rank>
CardSet<Suit, Rank> &CardSet<Suit, Rank>::operator>>(CardSet<Suit, Rank> &set)
{
    // is empty
    try
    {
        if (cards.empty())
        {
            throw std::runtime_error("fail");
        }
    }
    catch (...)
    {
        std::cout << "ERROR CAUGHT: cards is empty";
    }

    Card<Suit, Rank> lastCard = Card(this->cards.back().suit, this->cards.back().rank);
    // pushes equivalent last card            hands.at(playerNumber).collect(deck);

    set.cards.push_back(lastCard);

    this->cards.pop_back();

    return *this;
}

// check if the set has no cards
template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::is_empty()
{
    if (cards.empty())
    {
        return true;
    }
    return false;
}

template <typename Suit, typename Rank>
typename std::vector<Card<Suit, Rank>>::iterator CardSet<Suit, Rank>::getBeginIterator()
{
    return cards.begin();
}

template <typename Suit, typename Rank>

typename std::vector<Card<Suit, Rank>>::iterator CardSet<Suit, Rank>::getEndIterator()
{
    return cards.end();
}

template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::sort()
{
    std::sort(getBeginIterator(), getEndIterator(), compare_2<Suit, Rank>);
    std::sort(getBeginIterator(), getEndIterator(), compare_1<Suit, Rank>);
}

// shift all of the cards out of the CardSet and into the Deck
template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::collect(CardSet<Suit, Rank> &set)
{
    std::move<iter, std::back_insert_iterator<typename std::vector<Card<Suit, Rank>>>>(set.getBeginIterator(), set.getEndIterator(), std::back_inserter<typename std::vector<Card<Suit, Rank>>>(cards));
}

template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::collect_if(CardSet<Suit, Rank> &deck, std::function<bool(Card<Suit, Rank> &)> pred)
{

    std::copy_if<iter, std::back_insert_iterator<typename std::vector<Card<Suit, Rank>>>, std::function<bool(Card<Suit, Rank> &)>>(deck.getBeginIterator(), deck.getEndIterator(), std::back_inserter<typename std::vector<Card<Suit, Rank>>>(cards), pred);

    auto startOfUndefinedIter = std::remove_if<iter, std::function<bool(Card<Suit, Rank> &)>>(deck.getBeginIterator(), deck.getEndIterator(), pred);

    deck.cards.erase(startOfUndefinedIter, deck.getEndIterator());
}

template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::request(CardSet<Suit, Rank> &cardSet, rank_type &rank)
{
    if (cardSet.is_empty())
    {
        return false;
    }
    auto it = std::find_if(cardSet.getBeginIterator(), cardSet.getEndIterator(), [rank](Card<Suit, Rank> current)
                           { return current.rank == rank; });

    if (it == cardSet.getEndIterator())
    {
        return false;
    }

    // TODO figure out how to create pred for card==rank

    collect_if(cardSet, [rank](Card<Suit, Rank> card)
               { return (rank == card.rank); });

    return true;
}
