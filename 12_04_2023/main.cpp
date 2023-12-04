#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif

const int NUM_SUITS = 5;
const int NUM_FACE = 14;

enum suitType
{
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS,
    DEFAULTS
};

enum faceType
{
    A,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    J,
    Q,
    K,
    DEFAULTR
};

const faceType faces[] = {A,
                          TWO,
                          THREE,
                          FOUR,
                          FIVE,
                          SIX,
                          SEVEN,
                          EIGHT,
                          NINE,
                          TEN,
                          J,
                          Q,
                          K,
                          DEFAULTR};
const suitType suits[] = {HEARTS,
                          DIAMONDS,
                          SPADES,
                          CLUBS,
                          DEFAULTS};
const std::string faceStr[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", " "};
const std::string suitStr[] = {"♥", "♦", "♠", "♣", " "};
const int DECK_SIZE = 52;
const int NUM_PILES = 4;

struct cardType
{
    suitType suit = DEFAULTS;
    faceType face = DEFAULTR;
    bool used = false;
};
struct deckType
{
    cardType cards[DECK_SIZE];
    int next = -1;
    int remain = DECK_SIZE;
};
struct pileType
{
    cardType cards[DECK_SIZE];
    int topCard = -1;
};
std::string printCard(cardType theCard);
// lecture activity copy setUpDeck and add comments
void setUpDeck(deckType &theDeck, pileType foundations[]);

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    cardType myCard;
    myCard.suit = DEFAULTS;
    myCard.face = DEFAULTR;
    cardType yourCard;
    yourCard = myCard;
    // std::cin >> myCard;
    // std::cout << yourCard;
    yourCard.face = TWO;
    yourCard.suit = CLUBS;
    std::cout << printCard(yourCard) << std::endl;
}

std::string printCard(cardType theCard)
{
    std::string output; // A♥,  ♥A, or Ace of ♥
    output = faceStr[theCard.face] + suitStr[theCard.suit];
    return output;
}

void setUpDeck(deckType &theDeck, pileType foundations[])
{
    for (int i = 0; i < NUM_SUITS - 1; i++)
    {
        for (int j = 0; j < NUM_FACE - 1; j++)
        {
            theDeck.cards[i * (NUM_FACE - 1) + j].suit = suits[i];
            theDeck.cards[i * (NUM_FACE - 1) + j].face = faces[j];
            theDeck.cards[i * (NUM_FACE - 1) + j].used = false;
            foundations[i].cards[j].face = faces[((i + 1) * (j + 1) - 1) % 13]; // example math pile 3 (index 2) card 7 (index 6) (2+1)*(6+1) = 21 -1 = 20 % 13
        }
        foundations[i].topCard = -1;
    }
}
