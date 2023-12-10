// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementation of the overloaded operators << and == for the Card template, as well as functions compare_1 and compare_2.

#include "card_T.h"

// to print a card, print its suit and rank
template <typename S, typename R>
std::ostream &operator<<(std::ostream &write, const Card<S, R> &card)
{
	write << card.rank << card.suit;

	return write;
}

//compare by rank
//if rank same, then compare by suit
template <typename S, typename R>
bool compare_1(const Card<S, R> &card1, const Card<S, R> &card2)
{
	if (card1.rank < card2.rank)
	{
		return true;
	}
	else if (card1.rank == card2.rank)
	{
		return card1.suit < card2.suit;
	}
	return false;
}

//compare by suit
//if suit same, then compare by rank
template <typename S, typename R>
bool compare_2(const Card<S, R> &card1, const Card<S, R> &card2)
{
	if (card1.suit < card2.suit)
	{
		return true;
	}
	else if (card1.suit == card2.suit)
	{
		return card1.rank < card2.rank;
	}
	return false;
}

//to compare a card via ==, compare the card's rank and suit
template <typename S, typename R>
bool Card<S, R>::operator==(const Card<S, R> other) const
{
	if (this->rank == other.rank && this->suit == other.suit)
	{
		return true;
	}
	return false;
}