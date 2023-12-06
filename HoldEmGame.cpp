// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations of the HoldEmGame class's member functions.

#include "HoldEmGame.h"

// create a hand for each player in the game
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop)
{
    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pokerRank> current;
        hands.push_back(current);
    }
}

// distribute the next card(s) according to the current state of the game.
void HoldEmGame::deal()
{
    // if the state is preflop, then deal two cards to each player and then increment state
    if (state == HoldEmState::preflop)
    {

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }
        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }

        state = HoldEmState::flop;
    }
    // if the state is flop, then deal three cards to the board and increment state
    else if (state == HoldEmState::flop)
    {

        for (int i = 0; i < 3; i++)
        {
            deck >> board;
        }
        state = HoldEmState::turn;
    }
    // if the state is turn, then deal a card to the board and increment state
    else if (state == HoldEmState::turn)
    {
        deck >> board;
        state = HoldEmState::river;
    }
    // if the state is river, then deal a cards to the board and increment state
    else if (state == HoldEmState::river)
    {
        deck >> board;
        state = HoldEmState::undefined;
    }
}

// a single play in a Texas Hold Em game consists of these steps in the following order:
// 1. shuffle the deck
// 2. set the state to preflop
// 3. deal two cards to each hand and proceed to flop
// 4. print each player's cards
// 5. deal three cards to the board and proceed to turn
// 6. print all cards on the board
// 7. deal one more card to the board and proceed to river
// 8. print all cards on the board
// 9. deal one more card to the board
// 10. print all cards on the board
// 11. collect all players' cards and return them to deck
// 12. collect all board cards and return them to deck
// 13/14. ask to play another round and await input
int HoldEmGame::play()
{
    int NUM_FLOP_CARDS = 3;
    int NUM_TURN_CARDS = 4;
    int NUM_RIVER_CARDS = 5;

    bool end_game_flag = false;
    while (!end_game_flag)
    {
        deck.shuffle();
        state = HoldEmState::preflop;
        deal();
        printPlayersCurrentHands();
        deal();
        printBoard("flop", NUM_FLOP_CARDS);

        std::vector<values::hold> vec;

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            CardSet<Suit, pokerRank> hand;

            CardSet<Suit, pokerRank> localHand(hands.at(i));
            CardSet<Suit, pokerRank> localHand2(board);

            localHand >> hand;
            localHand >> hand;

            for (int j = 0; j < 3; j++)
            {
                localHand2 >> hand;
            }

            pokerRank firstTieBreaker;
            pokerRank secondTieBreaker;
            pokerRank thirdTieBreaker;
            pokerRank fourthTieBreaker;
            pokerRank fifthTieBreaker;

            HoldEmHandRank holdEmHandRank = holdem_hand_evaluation(hand, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker, fifthTieBreaker);

            std::vector<pokerRank> tieBreakers;

            tieBreakers.push_back(firstTieBreaker);
            tieBreakers.push_back(secondTieBreaker);
            tieBreakers.push_back(thirdTieBreaker);
            tieBreakers.push_back(fourthTieBreaker);
            tieBreakers.push_back(fifthTieBreaker);

            values::hold x = values::hold(hand, players.at(i), holdEmHandRank, tieBreakers);
            vec.push_back(x);
        }

        std::sort(vec.begin(), vec.end());

        for (auto it = vec.begin(); it != vec.end(); it++)
        {
            std::cout << "Player name: " << (*it).playerName << std::endl
                      << " cards: ";
            (*it).cards.print(std::cout, 5);
            std::cout << " Hand rank: " << (*it).holdEmHandRank << std::endl;
        }

        deal();
        printBoard("turn", NUM_TURN_CARDS);
        deal();
        printBoard("river", NUM_RIVER_CARDS);

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck.collect(hands.at(i));
        }
        deck.collect(board);
        end_game_flag = promptEndGame();
    }
    return SUCCESS;
}

// print every card on the board
void HoldEmGame::printBoard(const char *segment, int numCards)
{
    std::cout << "BOARD(" << segment << "):";
    board.print(std::cout, numCards);
}

// print every card in each of the players hands
void HoldEmGame::printPlayersCurrentHands()
{
    int counter = 0;
    int cards_in_hand = 2;
    std::vector<CardSet<Suit, pokerRank>>::iterator j = hands.begin();
    for (std::vector<std::string>::iterator i = players.begin(); i != players.end(); i++)
    {
        std::cout << *i << ": ";
        (*j).print(std::cout, cards_in_hand);
        std::cout << std::endl;
        counter++;
        j++;
    }
}

std::ostream &operator<<(std::ostream &stream, const HoldEmHandRank &rank)
{

    switch (rank)
    {

    case (HoldEmHandRank::xhigh):
        stream << "X High";
        break;

    case (HoldEmHandRank::pair):
        stream << "Pair";
        break;

    case (HoldEmHandRank::twopair):
        stream << "Two Pair";
        break;
    case (HoldEmHandRank::threeofakind):
        stream << "Three of a kind";
        break;
    case (HoldEmHandRank::straight):
        stream << "Straight";
        break;

    case (HoldEmHandRank::flush):
        stream << "Flush";
        break;

    case (HoldEmHandRank::fullhouse):
        stream << "Full House";
        break;
    case (HoldEmHandRank::fourofakind):
        stream << "Four of a kind";
        break;
    case (HoldEmHandRank::straightflush):
        stream << "Straight flush";
        break;
    case (HoldEmHandRank::undefined):
        stream << "Undefined hand";
        break;
    }
    return stream;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suit, pokerRank> &hand, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker, pokerRank &fifthTieBreaker)
{
    int const HAND_SIZE = 5;
    CardSet<Suit, pokerRank> localHand(hand);

    // std::vector<Card<Suit, pokerRank>> CardSet<Suit, pokerRank>::*memberCards = CardSet<Suit, pokerRank>::access_cards();

    // std::vector<Card<Suit, pokerRank>> cards = localHand.*memberCards;
    localHand.sort();

    auto begin = localHand.getBeginIterator();
    auto end = localHand.getEndIterator();
    auto card4 = (*(begin + 4)).rank;
    auto card3 = (*(begin + 3)).rank;
    auto card2 = (*(begin + 2)).rank;
    auto card1 = (*(begin + 1)).rank;
    auto card0 = (*(begin)).rank;

    int size = 0;

    auto copy = begin;

    while (copy != end)
    {
        size++;
        copy++;
    }

    // check for undefined
    if (size != HAND_SIZE)
    {
        return HoldEmHandRank::undefined;
    }

    // check for straighflush

    if (checkForStraight(begin, end, firstTieBreaker) && checkForFlush(begin, end))
    {
        return HoldEmHandRank::straightflush;
    }

    // check for four of a kind
    if (findXofaKind(begin, end, 4, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::fourofakind;
    }

    // check for fullhouse
    if (checkForFullHouse(begin, firstTieBreaker))
    {
        return HoldEmHandRank::fullhouse;
    }

    // check for flush
    if (checkForFlush(begin, end))
    {
        firstTieBreaker = card4;
        secondTieBreaker = card3;
        thirdTieBreaker = card2;
        fourthTieBreaker = card1;
        fifthTieBreaker = card0;

        return HoldEmHandRank::flush;
    }

    // check for straight
    if (checkForStraight(begin, end, firstTieBreaker))
    {
        return HoldEmHandRank::straight;
    }

    // check for threeofakind
    if (findXofaKind(begin, end, 3, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::threeofakind;
    }
    // check for two pair

    if ((card0 == card1 && (card2 == card3)) || ((card0 == card1) && (card3 == card4)) || ((card1 == card2 && (card3 == card4))))
    {
        pokerRank highPair = card3;

        pokerRank lowPair = card1;
        pokerRank nonPair;

        if (card4 != card3)
        {
            nonPair = card4;
        }
        else
        {
            if (card1 == card2)
            {
                nonPair = card0;
            }
            else
            {
                nonPair = card2;
            }
        }

        firstTieBreaker = highPair;
        secondTieBreaker = lowPair;
        thirdTieBreaker = nonPair;

        return HoldEmHandRank::twopair;
    }

    // check for pair
    if (findXofaKind(begin, end, 2, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::pair;
    }

    firstTieBreaker = (*(begin + 4)).rank;
    secondTieBreaker = (*(begin + 3)).rank;
    thirdTieBreaker = (*(begin + 2)).rank;
    fourthTieBreaker = (*(begin + 1)).rank;
    fifthTieBreaker = (*(begin)).rank;

    return HoldEmHandRank::xhigh;
}
/*
// only called when findXofaKind's counter is 2
// check if the type of hand is a three of a kind or two pairs
bool checkFor3Kind(std::vector<Card<Suit, pokerRank>>::iterator begin, std::vector<Card<Suit, pokerRank>>::iterator end)
{
    // case 1
    if (hand.at(0).rank == hand.at(1).rank && hand.at(2).rank == hand.at(1).rank)
    {
        return true;
    }

    // case 2

    if (hand.at(1).rank == hand.at(2).rank && hand.at(2).rank == hand.at(3).rank)
    {
        return true;
    }
    // case 3
    if (hand.at(2).rank == hand.at(3).rank && hand.at(4).rank == hand.at(4).rank)
    {
        return true;
    }
    // if we have reached here, then no three pair was found, so it must be two pairs
    return false;
}
*/

bool checkForFullHouse(std::vector<Card<Suit, pokerRank>>::iterator begin, pokerRank &firstTieBreaker)
{

    // two cases: first three same and last two same
    // or first two same and last three same

    if (((*begin).rank == (*(begin + 1)).rank) && (*(begin + 1)).rank == ((*(begin + 2))).rank && (*(begin + 3)).rank == (*(begin + 4)).rank)
    {
        firstTieBreaker = (*begin).rank;

        return true;
    }

    if ((((*(begin + 2))).rank == (*(begin + 3)).rank) && ((*(begin + 3)).rank == (*(begin + 4)).rank) && ((*(begin)).rank == (*(begin + 1)).rank))
    {
        firstTieBreaker = (*(begin + 4)).rank;

        return true;
    }

    return false;
}

bool checkForStraight(std::vector<Card<Suit, pokerRank>>::iterator begin, std::vector<Card<Suit, pokerRank>>::iterator end, pokerRank &firstTieBreaker)
{

    pokerRank starting = (*begin).rank;

    if (starting >= pokerRank::jack)
    {
        return false;
    }

    std::vector<Card<Suit, pokerRank>>::iterator next = begin + 1;

    for (std::vector<Card<Suit, pokerRank>>::iterator it = begin; it != end - 1; it++)
    {
        if ((*next).rank != static_cast<pokerRank>((static_cast<int>((*it).rank)) + 1))
        {
            return false;
        }
        next++;
    }

    firstTieBreaker = (*next).rank;

    return true;
}
bool checkForFlush(std::vector<Card<Suit, pokerRank>>::iterator begin, std::vector<Card<Suit, pokerRank>>::iterator end)
{
    Suit first = (*begin).suit;

    return (std::count_if(begin + 1, end, [&first](Card<Suit, pokerRank> card)
                          { return card.suit == first; }) == 4);
}
bool findXofaKind(std::vector<Card<Suit, pokerRank>>::iterator begin, std::vector<Card<Suit, pokerRank>>::iterator end, int x, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker)
{

    std::vector<Card<Suit, pokerRank>>::iterator pnt1 = begin;
    std::vector<Card<Suit, pokerRank>>::iterator pnt2 = begin + 1;

    int counter = 0;

    while (pnt2 != end && counter < (x - 1))
    {

        if ((*pnt1).rank != (*pnt2).rank)
        {
            pnt1++;

            counter = 0;
        }
        else
        {

            counter++;
        }

        pnt2++;
    }

    // 1 for pair
    // 2 for threeofakind
    // 3 for fourofakind

    int const PAIR_VALUE = 1;
    int const THREE_OF_A_KIND_VALUE = 2;
    int const FOUR_OF_A_KIND_VALUE = 3;
    if (counter == (x - 1))
    {
        // have a pair
        if (counter == PAIR_VALUE)
        {

            pokerRank pairValue;
            std::vector<Card<Suit, pokerRank>>::iterator it = begin;
            std::vector<Card<Suit, pokerRank>>::iterator next = begin + 1;

            // find pair rank first
            for (; it != end - 1; it++)
            {
                if ((*it).rank == (*next).rank)
                {
                    pairValue = ((*it).rank);
                    break;
                }
                next++;
            }

            // set next highest card tiebreakers
            auto rt = end;

            std::vector<pokerRank> tieBreakValues;

            for (; rt != begin - 1; --rt)
            {
                if ((*rt).rank == pairValue)
                {
                    --rt;
                }
                else
                {
                    tieBreakValues.push_back((*rt).rank);
                }
            }
            firstTieBreaker = pairValue;
            secondTieBreaker = tieBreakValues.at(0);
            thirdTieBreaker = tieBreakValues.at(1);
            fourthTieBreaker = tieBreakValues.at(2);
        }

        if (counter == THREE_OF_A_KIND_VALUE)
        {

            pokerRank threeOfAKindRank = (*(begin + 2)).rank;

            firstTieBreaker = threeOfAKindRank;
        }

        if (counter == FOUR_OF_A_KIND_VALUE)
        {
            firstTieBreaker = (*(begin + 3)).rank;
        }

        return true;
    }
    return false;
}

bool operator<(const HoldEmGame::values::hold &x, const HoldEmGame::values::hold &y)
{

    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int xSecondTieBreaker = static_cast<int>(x.tieBreakers.at(1));
    int xThirdBreaker = static_cast<int>(x.tieBreakers.at(2));
    int xFourthTieBreaker = static_cast<int>(x.tieBreakers.at(3));
    int xFifthTieBreaker = static_cast<int>(x.tieBreakers.at(4));

    int yFirstTieBreaker = static_cast<int>(y.tieBreakers.at(0));
    int ySecondTieBreaker = static_cast<int>(y.tieBreakers.at(1));
    int yThirdTieBreaker = static_cast<int>(y.tieBreakers.at(2));
    int yFourthTieBreaker = static_cast<int>(y.tieBreakers.at(3));
    int yFifthTieBreaker = static_cast<int>(y.tieBreakers.at(4));

    if (static_cast<int>(x.holdEmHandRank) < static_cast<int>(y.holdEmHandRank))
    {
        return true;
    }

    else if (static_cast<int>(x.holdEmHandRank) > static_cast<int>(y.holdEmHandRank))
    {
        return false;
    }

    else if (xFirstTieBreaker > yFirstTieBreaker)
    {
        return false;
    }
    else if (xFirstTieBreaker < yFirstTieBreaker)
    {
        return true;
    }

    else if (xSecondTieBreaker > ySecondTieBreaker)
    {
        return false;
    }
    else if (xSecondTieBreaker < ySecondTieBreaker)
    {
        return true;
    }
    else if (xThirdBreaker > yThirdTieBreaker)
    {
        return false;
    }
    else if (xThirdBreaker < yThirdTieBreaker)
    {
        return true;
    }
    else if (xFourthTieBreaker > yFourthTieBreaker)
    {
        return false;
    }
    else if (xFourthTieBreaker < yFourthTieBreaker)
    {
        return true;
    }

    else if (xFifthTieBreaker > yFifthTieBreaker)
    {
        return false;
    }
    else if (xFifthTieBreaker < yFifthTieBreaker)
    {
        return true;
    }

    return false;
}
