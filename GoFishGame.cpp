// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the definitions for the GoFishGame class.
// This includes definitions for member functions collect_books(), turn(), deal(), and play()

#include "GoFishGame.h"
#include <unordered_map>
#include "Uno.h"
#include "pinochle.h"
#include <type_traits>
#include <variant>

//method to control the go fish game
//add as many hands are there are players
//then check that there are at least 4 cards of each rank in the deck. if not, throw exception.
template <typename Suit, typename Rank, typename Deck>

GoFishGame<Suit, Rank, Deck>::GoFishGame(int numPlayers, const char *playerNames[]) : Game(numPlayers, playerNames), numPlayers(numPlayers)
{

    for (int i = 3; i < numPlayers + 3; i++)
    {
        players.push_back((playerNames[i]));
        CardSet<Suit, Rank> current;
        hands.push_back(current);
        books.push_back(current);
    }

    deck = Deck();

    Rank rank = static_cast<Rank>(0);

    std::cout << "type: " << typeid(Rank).name() << std::endl;

    std::vector<Rank> trackRanks;

    // check if deck valid
    while (std::find(trackRanks.begin(), trackRanks.end(), rank) == trackRanks.end())
    {
        std::cout << "Rank: " << rank << std::endl;
        trackRanks.push_back(rank);

        int num = std::count_if(deck.getBeginIterator(), deck.getEndIterator(), [rank](Card<Suit, Rank> card)
                                { return (card.rank == rank); });

        std::cout << "NUM: " << num << std::endl;
        if (num < 4)
        {
            throw std::runtime_error("Deck Invalid");
        }

        rank = static_cast<Rank>(static_cast<int>(rank) + 1);
    }
}

//template specialization of GoFishGame for Uno cards
template <>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int numPlayers, const char *playerNames[]) : Game(numPlayers, playerNames), numPlayers(numPlayers)
{

    for (int i = 3; i < numPlayers + 3; i++)
    {
        players.push_back((playerNames[i]));
        CardSet<Color, UnoRank> current;
        hands.push_back(current);
        books.push_back(current);
    }

    deck = UnoDeck();

    UnoRank rank = static_cast<UnoRank>(0);

    std::vector<UnoRank> trackRanks;

    // check if deck valid
    while (std::find(trackRanks.begin(), trackRanks.end(), rank) == trackRanks.end() && rank != UnoRank::undefined)
    {
        std::cout << "Rank: " << rank << std::endl;
        trackRanks.push_back(rank);

        int num = std::count_if(deck.getBeginIterator(), deck.getEndIterator(), [rank](Card<Color, UnoRank> card)
                                { return (card.rank == rank); });

        std::cout << "NUM: " << num << std::endl;
        if (num < 4)
        {
            // TODO
            throw std::runtime_error("Deck Invalid");
        }

        rank = static_cast<UnoRank>(static_cast<int>(rank) + 1);
    }
}

//template specialization of GoFishGame for pinochle cards
template <>
GoFishGame<Suit, pinRank, pinochleDeck>::GoFishGame(int numPlayers, const char *playerNames[]) : Game(numPlayers, playerNames), numPlayers(numPlayers)
{

    for (int i = 3; i < numPlayers + 3; i++)
    {
        players.push_back((playerNames[i]));
        CardSet<Suit, pinRank> current;
        hands.push_back(current);
        books.push_back(current);
    }
    deck = pinochleDeck();

    pinRank rank = static_cast<pinRank>(0);

    std::vector<pinRank> trackRanks;

    // check if deck valid
    while (std::find(trackRanks.begin(), trackRanks.end(), rank) == trackRanks.end() && rank != pinRank::undefined)
    {
        std::cout << "Rank: " << rank << std::endl;
        trackRanks.push_back(rank);

        int num = std::count_if(deck.getBeginIterator(), deck.getEndIterator(), [rank](Card<Suit, pinRank> card)
                                { return (card.rank == rank); });

        std::cout << "NUM: " << num << std::endl;
        if (num < 4)
        {
            // TODO
            throw std::runtime_error("Deck Invalid");
        }

        rank = static_cast<pinRank>(static_cast<int>(rank) + 1);
    }
}

//template specialization of GoFishGame for poker cards
template <>
GoFishGame<Suit, pokerRank, pokerDeck>::GoFishGame(int numPlayers, const char *playerNames[]) : Game(numPlayers, playerNames), numPlayers(numPlayers)
{

    for (int i = 3; i < numPlayers + 3; i++)
    {
        players.push_back((playerNames[i]));
        CardSet<Suit, pokerRank> current;
        hands.push_back(current);
        books.push_back(current);
    }

    deck = pokerDeck();

    pokerRank rank = static_cast<pokerRank>(1);

    std::vector<pokerRank> trackRanks;
    int count = 0;

    // check if deck valid
    while (std::find(trackRanks.begin(), trackRanks.end(), rank) == trackRanks.end() && count < 13)
    {
        std::cout << "Rank: " << rank << std::endl;
        trackRanks.push_back(rank);

        int num = std::count_if(deck.getBeginIterator(), deck.getEndIterator(), [rank](Card<Suit, pokerRank> card)
                                { return (card.rank == rank); });

        std::cout << "NUM: " << num << std::endl;
        if (num < 4)
        {
            // TODO
            throw std::runtime_error("Deck Invalid");
        }

        ++rank;
        count++;
    }
}

//given a player number, check if there is a 4-of-a-kind in that player's hand, and return a boolean value to indicate whether or not 4 cards of the same rank were found in it.
//if 4-of-a-kind, call collect_if() to move cards of appropriate rank from hand to CardSet of books player has made and return true
//else return false
template <typename Suit, typename Rank, typename Deck>
bool GoFishGame<Suit, Rank, Deck>::collect_books(int playerNumber)

{
    CardSet<Suit, Rank> &hand = hands.at(playerNumber);

    // for every card in hand count if there is 4
    for (auto it = hand.getBeginIterator(); it != hand.getEndIterator(); it++)
    {
        Rank rank = (*it).rank;
        int count = std::count_if(hand.getBeginIterator(), hand.getEndIterator(), [rank](Card<Suit, Rank> current)
                                  { return current.rank == rank; });
        if (count >= 4)
        {

            books.at(playerNumber).collect_if(hand, [rank](Card<Suit, Rank> current)
                                              { return current.rank == rank; });
            return true;
        }
    }
    return false;
}

//map the ranks of a given rank type to a corresponding descriptive string
std::unordered_map<std::string, UnoRank> unoPairings = {{"zero", UnoRank::zero},
                                                        {"one", UnoRank::one},
                                                        {"two", UnoRank::two},
                                                        {"three", UnoRank::three},
                                                        {"four", UnoRank::four},
                                                        {"five", UnoRank::five},
                                                        {"six", UnoRank::six},
                                                        {"seven", UnoRank::seven},
                                                        {"eight", UnoRank::eight},
                                                        {"nine", UnoRank::nine},
                                                        {"skip", UnoRank::skip},
                                                        {"reverse", UnoRank::reverse},
                                                        {"drawtwo", UnoRank::drawtwo},
                                                        {"drawfour", UnoRank::drawfour},
                                                        {"wild", UnoRank::wild},
                                                        {"blank", UnoRank::blank}};

std::unordered_map<std::string, pokerRank> pokerPairings = {{"two", pokerRank::two},
                                                            {"three", pokerRank::three},
                                                            {"four", pokerRank::four},
                                                            {"five", pokerRank::five},
                                                            {"six", pokerRank::six},
                                                            {"seven", pokerRank::seven},
                                                            {"eight", pokerRank::eight},
                                                            {"nine", pokerRank::nine},
                                                            {"ten", pokerRank::ten},
                                                            {"jack", pokerRank::jack},
                                                            {"queen", pokerRank::queen},
                                                            {"king", pokerRank::king},
                                                            {"ace", pokerRank::ace}};
std::unordered_map<std::string, pinRank> pinPairings = {{"nine", pinRank::nine},
                                                        {"ten", pinRank::ten},
                                                        {"jack", pinRank::jack},
                                                        {"queen", pinRank::queen},
                                                        {"king", pinRank::king},
                                                        {"ace", pinRank::ace}};

//next three functions are function to match a given rank with its corresponding descriptive string in the above unordered maps

//function overload for unorank
bool findMatch(UnoRank &rank, std::string rankString)
{
    std::unordered_map<std::string, UnoRank>::iterator it = unoPairings.find(rankString);

    if (it != unoPairings.end())
    {
        rank = it->second;
        return true;
    }
    return false;
}
//function overload for pinRank
bool findMatch(pinRank &rank, std::string rankString)
{

    std::unordered_map<std::string, pinRank>::iterator it = pinPairings.find(rankString);

    if (it != pinPairings.end())
    {
        rank = it->second;
        return true;
    }
    return false;
}

//function overload for pokerRank
bool findMatch(pokerRank &rank, std::string rankString)
{
    std::unordered_map<std::string, pokerRank>::iterator it = pokerPairings.find(rankString);

    if (it != pokerPairings.end())
    {
        rank = it->second;

        return true;
    }
    return false;
}

//given number of players, return a boolean value to indicate whether it still remains that player's turn.
//print out the players hands and books and then prompt the user to indicate what card rank to ask for and what player to ask for it from
//repeat until user provides a valid card rank (which must be the rank of a card in the player's hand) and player number (which must be the number of a player in the game).
//then use request() to try to obtain a card of that rank from the targeted player
//if successful, repeatedly call the collect_books method for the player whose turn it is until the collect_books returns false; and then return true.
//If unsuccessful, "go fish" by drawing a card from the deck into the hand of the player whose turn it is. 
//If deck is empty, move all of current player's cards into deck and remove current player; then return false.
template <typename Suit, typename Rank, typename Deck>
bool GoFishGame<Suit, Rank, Deck>::turn(int playerNumber)
{

    bool game = true;
    if (deck.is_empty())
    {
        game = false;
    }

    for (int i = 0; i < numPlayers; i++)
    {
        if (!hands.at(i).is_empty())
        {
            game = true;
        }
    }

    // 1 or 0 players left end game
    if (static_cast<int>(removedPlayerList.size()) == numPlayers || static_cast<int>(removedPlayerList.size()) == numPlayers - 1)
    {

        game = false;
    }

    if (game == false)
    {
        return false;
    }

    // removed player doesn't take a turn
    if (std::find(removedPlayerList.begin(), removedPlayerList.end(), playerNumber) != removedPlayerList.end())
    {
        return false;
    }

    // draw card if have empty hand
    if (hands.at(playerNumber).is_empty())
    {
        // remove player from game if drawing deck empty and they have no cards after all cards turned into books
        if (deck.is_empty() && hands.at(playerNumber).is_empty())
        {

            std::cout << "player: " << playerNumber << " removed from game" << std::endl;
            removedPlayerList.push_back(playerNumber);
        }
        return false;

        deck >> hands.at(playerNumber);
    }
    // print players current hands and books

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << "PLAYER: " << players.at(i) << std::endl;
        hands.at(i).print(std::cout, 100);
        std::cout << std::endl;
        std::cout << "Books: ";
        books.at(i).print(std::cout, 4);
        std::cout << std::endl;
    }

    int playerNumTarget;

    Rank rank;

    std::string rankString;

    std::cout << "TURN OF player: " << players.at(playerNumber) << std::endl;

    bool findMatchBool = false;

    std::cout << "What card rank and what player number? enter as rank number SPACE player number" << std::endl;
    std::cin >> rankString;
    std::cin >> playerNumTarget;
    findMatchBool = findMatch(rank, rankString);

    while (std::find(removedPlayerList.begin(), removedPlayerList.end(), playerNumTarget) != removedPlayerList.end() || playerNumTarget == playerNumber || !findMatchBool || playerNumTarget >= numPlayers || playerNumTarget < 0 || std::find_if(hands.at(playerNumber).getBeginIterator(), hands.at(playerNumber).getEndIterator(), [rank](Card<Suit, Rank> x)
                                                                                                                                                                                                                                                  { return (x.rank == rank); }) == hands.at(playerNumber).getEndIterator())
    {
        std::cout << "What card rank and what player number? enter as rank number SPACE player number" << std::endl;
        std::cin >> rankString;
        std::cin >> playerNumTarget;
        findMatchBool = findMatch(rank, rankString);
        std::cin.clear();
    };

    bool requestResult = hands.at(playerNumber).request(hands.at(playerNumTarget), rank);

    if (requestResult)
    {

        while (collect_books(playerNumber))
        {
        }
        // remove player from game if drawing deck empty and they have no cards after all cards turned into books
        if (deck.is_empty() && hands.at(playerNumber).is_empty())
        {

            std::cout << "player: " << playerNumber << " removed from game" << std::endl;
            removedPlayerList.push_back(playerNumber);
        }

        return true;
    }
    else
    {
        std::cout << "Go fish" << std::endl;

        // remove player from game if drawing deck empty
        if (deck.is_empty())
        {

            std::cout << "player: " << playerNumber << " removed from game" << std::endl;
            deck.collect(hands.at(playerNumber));
            removedPlayerList.push_back(playerNumber);
        }
        // draw from deck
        else
        {
            deck >> hands.at(playerNumber);
            Card<Suit, Rank> card = *(hands.at(playerNumber).getEndIterator() - 1);

            if (card.rank == rank)
            {

                return true;
            }
            return false;
        }
        return false;
    }
}

// Shuffle the deck and deal each player 1 card at a time until each player has received the proper number of cards.
// If there are only two players in the game, each player should receive seven cards, or if there are more than two players in the game, each player should receive five cards.
template <typename Suit, typename Rank, typename Deck>
void GoFishGame<Suit, Rank, Deck>::deal()
{

    deck.shuffle();

    if (numPlayers == 2)
    {

        int current_player_num = 0;

        for (int i = 0; i < 14; i++)
        {
            deck >> hands.at(current_player_num);

            current_player_num++;
            if (current_player_num >= numPlayers)
            {
                current_player_num = 0;
            }
        }
    }
    // more than two players
    else
    {

        for (auto it = hands.begin(); it != hands.end(); it++)
        {
            for (int i = 0; i < 5; i++)
            {
                deck >> *it;
            }
        }
    }
}

// Start by calling deal and then for each player number repeatedly call the collect_books method with that player number until it returns false. 
// Then, repeatedly iterate over all players that remain in the game, in multiple rounds until the game ends. 
// In each round, for each player in succession, repeatedly call the turn method for the (same) current player until it returns false and then advance to the next player.
// The game is over when all cards have moved from the deck and the players' hands into the players' collections of books, or when there is one or zero players left in the game. 
// Once the game has finished, it should say which player (or players) has made the most books.
template <typename Suit, typename Rank, typename Deck>
int GoFishGame<Suit, Rank, Deck>::play()
{
    deal();

    int mostBooksCount = 0;

    std::vector<int> mostBooksIndex;

    for (int i = 0; i < numPlayers; i++)
    {

        while (collect_books(i))
        {
        }
    }

    bool game = true;
    int round = 0;
    while (game)
    {
        round++;

        for (int i = 0; i < numPlayers; i++)
        {
            // skip removed players turn
            if (std::find(removedPlayerList.begin(), removedPlayerList.end(), i) != removedPlayerList.end())
            {
                continue;
            }
            while (turn(i))
            {

                for (int i = 0; i < numPlayers; i++)
                {

                    while (collect_books(i))
                    {
                    }
                }
            }

            if (deck.is_empty())
            {
                game = false;
            }

            for (int i = 0; i < numPlayers; i++)
            {
                if (!hands.at(i).is_empty())
                {
                    game = true;
                }
            }

            // 1 or 0 players left end game
            if (static_cast<int>(removedPlayerList.size()) == numPlayers || static_cast<int>(removedPlayerList.size()) == numPlayers - 1)
            {

                game = false;
            }

            if (game == false)
            {
                break;
            }
        }
        std::cout << "book count: ";
        for (int i = 0; i < numPlayers; i++)
        {
            int bookSize = std::distance(books.at(i).getBeginIterator(), books.at(i).getEndIterator());

            std::cout << "player: " << players.at(i) << ": " << bookSize / 4 << std::endl;
            if (bookSize / 4 > mostBooksCount)
            {
                mostBooksIndex.clear();

                mostBooksIndex.push_back(i);
                mostBooksCount = bookSize / 4;
            }
            else if (bookSize / 4 == mostBooksCount)
            {

                mostBooksIndex.push_back(i);
            }
        }

        std::cout << "round number: " << round << std::endl;

        if (deck.is_empty())
        {
            game = false;
        }

        for (int i = 0; i < numPlayers; i++)
        {
            if (!hands.at(i).is_empty())
            {
                game = true;
            }
        }

        // 1 or 0 players left end game
        if (static_cast<int>(removedPlayerList.size()) == numPlayers || static_cast<int>(removedPlayerList.size()) == numPlayers - 1)
        {

            game = false;
        }
    }

    std::cout << "game over. player(s) w/ most books: " << std::endl;
    for (long unsigned int i = 0; i < mostBooksIndex.size(); i++)
    {
        std::cout << mostBooksIndex.at(i) << " , ";
    }
    std::cout << "winning book count: " << mostBooksCount << std::endl;
    return SUCCESS;
}
