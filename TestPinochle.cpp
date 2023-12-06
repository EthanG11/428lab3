#include "PinochleGame.h"
void suit_independent_evaluation(const CardSet<Suit, pinRank> &hand, std::vector<PinochleMelds> &vec)
{

    CardSet<Suit, pinRank> localHand(hand);

    // std::vector<Card<Suit, pinRank>> CardSet<Suit, pinRank>::*memberCards = CardSet<Suit, pinRank>::access_cards();
    localHand.sort();
    std::cout << "sorted" << std::endl;
    localHand.print(std::cout, 12);
    auto begin = localHand.getBeginIterator();
    auto end = localHand.getEndIterator();

    auto begin1 = localHand.getBeginIterator();
    auto end1 = localHand.getEndIterator();

    // std::vector<Card<Suit, pinRank>> cards = localHand.*memberCards;

    checkEightAndFourMelds(begin, end, pinRank::ace, vec);
    checkEightAndFourMelds(begin, end, pinRank::king, vec);
    checkEightAndFourMelds(begin, end, pinRank::queen, vec);
    checkEightAndFourMelds(begin, end, pinRank::jack, vec);

    Card<Suit, pinRank> jackDiamond(Suit::diamonds, pinRank::jack);
    Card<Suit, pinRank> queenSpade(Suit::spades, pinRank::queen);

    // return first iterator of jackDiamond
    auto jackTest = std::find_if(
        begin1, end1, [jackDiamond](Card<Suit, pinRank> current)
        { return current == jackDiamond; });

    // return first iterator of queenSpade
    auto queenTest = std::find_if(
        begin1, end1, [queenSpade](Card<Suit, pinRank> current)
        { return current == queenSpade; });

    // have a pinochle
    if (jackTest != end1 && queenTest != end1)
    {

        std::cout << "HERE" << std::endl;
        // test for doublepinochle
        if (*(++jackTest) == jackDiamond && *(++queenTest) == queenSpade)
        {
            vec.push_back(PinochleMelds::doublepinochle);
        }
        else
        {
            vec.push_back(PinochleMelds::pinochle);
        }
    }
};

int main()
{

    CardSet<Suit, pinRank> doublepin;

    Card<Suit, pinRank> aceSpades(Suit::spades, pinRank::ace);
    Card<Suit, pinRank> aceHearts(Suit::hearts, pinRank::ace);
    Card<Suit, pinRank> aceDiamonds(Suit::diamonds, pinRank::ace);
    Card<Suit, pinRank> aceClubs(Suit::clubs, pinRank::ace);

    Card<Suit, pinRank> jackDiamond(Suit::diamonds, pinRank::jack);
    Card<Suit, pinRank> queenSpade(Suit::spades, pinRank::queen);

    doublepin << aceSpades;

    doublepin.push_back(aceSpades);
    doublepin.push_back(aceSpades);
    doublepin.push_back(queenSpade);

    doublepin.push_back(aceSpades);
    doublepin.push_back(aceSpades);
    doublepin.push_back(jackDiamond);

    doublepin.push_back(aceSpades);
    doublepin.push_back(aceSpades);
    doublepin.push_back(aceSpades);
    doublepin.push_back(jackDiamond);

    doublepin.push_back(aceSpades);
    doublepin.push_back(queenSpade);

    std::vector<PinochleMelds> vec;

    suit_independent_evaluation(doublepin, vec);

    /*
    std::vector<Card<Suit, pinRank>> fourAcesCards;

    Card<Suit, pinRank> kingSpades(Suit::spades, pinRank::king);

    Card<Suit, pinRank> aceSpades(Suit::spades, pinRank::ace);
    Card<Suit, pinRank> aceHearts(Suit::hearts, pinRank::ace);
    Card<Suit, pinRank> aceDiamonds(Suit::diamonds, pinRank::ace);
    Card<Suit, pinRank> aceClubs(Suit::clubs, pinRank::ace);

    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);

    fourAcesCards.push_back(aceSpades);
    fourAcesCards.push_back(aceHearts);
    fourAcesCards.push_back(aceDiamonds);
    fourAcesCards.push_back(aceClubs);

    std::vector<PinochleMelds> melds1;

    pinRank card = pinRank::ace;

    checkEightAndFourMelds(fourAcesCards, card, melds1);

    if (melds1.size() == 1 && melds1.at(0) == PinochleMelds::hundredaces)
    {
        std::cout << "success hundredaces" << std::endl;
    }

    else
    {
        std::cout << melds1.size();
        std::cout << "FAIL";
    }

    std::vector<Card<Suit, pinRank>> eightAcesCards;
    std::vector<PinochleMelds> melds2;
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(aceClubs);
    eightAcesCards.push_back(aceDiamonds);
    eightAcesCards.push_back(aceHearts);
    eightAcesCards.push_back(aceSpades);
    eightAcesCards.push_back(aceClubs);
    eightAcesCards.push_back(aceDiamonds);
    eightAcesCards.push_back(aceHearts);
    eightAcesCards.push_back(aceSpades);

    checkEightAndFourMelds(eightAcesCards, card, melds2);

    if (melds2.size() == 1 && melds2.at(0) == PinochleMelds::thousandaces)
    {
        std::cout << "success thousandaces" << std::endl;
    }
    else
    {
        std::cout << "FAIL";
    }
    return 0;
    */
}