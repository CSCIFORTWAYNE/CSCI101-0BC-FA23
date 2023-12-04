#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <string>
#include <cstdlib>
#include <sstream>
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
std::string printASCIICard(cardType theCard);
std::string printASCIIPiles(pileType piles[], int numPiles);
std::string printGamePlayArea(pileType foundations[], pileType wastes[], deckType &theDeck, bool drawnCard);
// lecture activity copy setUpDeck and add comments
void setUpDeck(deckType &theDeck, pileType foundations[]);
void shuffleDeck(deckType &theDeck);
void setUpFirstFoundationCard(deckType &theDeck, pileType foundations[]);
int displayMenu(bool drawnCard, bool waste, bool noCards);
void resetStream();

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    deckType gameDeck;
    pileType foundations[NUM_PILES];
    pileType wastePiles[NUM_PILES];
    setUpDeck(gameDeck, foundations);
    shuffleDeck(gameDeck);
    setUpFirstFoundationCard(gameDeck, foundations);
    bool finished = false;
    bool drawnCard = false;
    int choice;
    while (!finished)
    {
        std::cout << printGamePlayArea(foundations, wastePiles, gameDeck, drawnCard);
        bool isWaste, noCards;
        isWaste = false;
        for (int i = 0; i < NUM_PILES; i++)
        {
            if (wastePiles[i].topCard > -1)
            {
                isWaste = true;
            }
        }
        noCards = gameDeck.remain <= 0;
        choice = displayMenu(drawnCard, isWaste, noCards);

        break;
    }
    /*     std::cout << printASCIICard(gameDeck.cards[0]) << std::endl;

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
        std::cout << printASCIICard(myCard) << std::endl;
        foundations[0].cards[0].suit = HEARTS;
        foundations[0].topCard = 0;
        std::cout << printASCIIPiles(foundations, NUM_PILES) << std::endl; */
}

std::string printCard(cardType theCard)
{
    std::string output; // A♥,  ♥A, or Ace of ♥
    output = faceStr[theCard.face] + suitStr[theCard.suit];
    return output;
}

std::string printASCIICard(cardType theCard)
{
    std::ostringstream output;
    if (theCard.face != DEFAULTR && theCard.suit != DEFAULTS)
    {
        output << "┌─────────┐ " << std::endl;
        output << std::setfill(' ') << std::left;
        output << "│ " << std::setw(8);
        output << faceStr[theCard.face];
        output << "│ " << std::endl;
        output << "│" << std::setw(9) << " "
               << "│ " << std::endl;
        output << std::right;
        output << "│" << std::setw(7);
        output << suitStr[theCard.suit];
        output << std::setw(4) << " "
               << "│ " << std::endl;
        output << "│" << std::setw(9) << " "
               << "│ " << std::endl;
        output << "│" << std::setw(8);
        output << faceStr[theCard.face];
        output << " │ " << std::endl;
        output << "└─────────┘ " << std::endl;
    }
    else
    {
        output << "┌─────────┐" << std::endl;
        output << "│░░░░░░░░░│" << std::endl;
        output << "│░░░░░░░░░│" << std::endl;
        output << "│░░░░░░░░░│" << std::endl;
        output << "│░░░░░░░░░│" << std::endl;
        output << "│░░░░░░░░░│" << std::endl;
        output << "└─────────┘" << std::endl;
    }

    return output.str();
}

std::string printASCIIPiles(pileType piles[], int numPiles)
{
    std::ostringstream output;
    for (int i = 0; i < numPiles; i++)
    {
        output << " ┌─────────┐ ";
    }
    output << std::endl
           << " ";
    for (int i = 0; i < numPiles; i++)
    {
        output << std::setfill(' ') << std::left;
        output << "│ " << std::setw(8);
        if (piles[i].topCard > -1)
        {
            output << faceStr[piles[i].cards[piles[i].topCard].face];
        }
        else
        {
            output << " ";
        }
        output << "│  ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << " │" << std::setw(9) << " "
               << "│ ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << std::right;
        output << " │";
        if (piles[i].topCard > -1)
        {
            output << std::setw(7);
            output << suitStr[piles[i].cards[piles[i].topCard].suit];
        }
        else
        {
            output << std::setw(5);
            output << " ";
        }
        output << std::setw(4) << " "
               << "│ ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << " │" << std::setw(9) << " "
               << "│ ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << " │" << std::setw(8);
        if (piles[i].topCard > -1)
        {
            output << faceStr[piles[i].cards[piles[i].topCard].face];
        }
        else
        {
            output << " ";
        }
        output << " │ ";
    }
    output << std::endl;

    for (int i = 0; i < numPiles; i++)
    {
        output << " └─────────┘ ";
    }
    output << std::endl;
    return output.str();
}

std::string printGamePlayArea(pileType foundations[], pileType wastes[], deckType &theDeck, bool drawnCard)
{
    std::ostringstream output;
    output << "Foundation Piles:" << std::endl;
    output << printASCIIPiles(foundations, NUM_PILES) << std::endl;
    output << "Waste Piles:" << std::endl;
    output << printASCIIPiles(wastes, NUM_PILES) << std::endl;
    if (drawnCard)
    {
        output << "Drawn Card:" << std::endl;
        output << printASCIICard(theDeck.cards[theDeck.next]) << std::endl;
    }
    else
    {
        output << "Remaining Cards (" << theDeck.remain << ")" << std::endl;
        cardType c;
        output << printASCIICard(c);
    }
    return output.str();
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

void shuffleDeck(deckType &theDeck)
{
    cardType shuffled[DECK_SIZE];
    for (int i = 0; i < DECK_SIZE; i++)
    {
        int shuffledCardIndex;
        do
        {
            shuffledCardIndex = rand() % DECK_SIZE;
        } while (theDeck.cards[shuffledCardIndex].used);
        shuffled[i] = theDeck.cards[shuffledCardIndex];
        theDeck.cards[shuffledCardIndex].used = true;
    }
    for (int i = 0; i < DECK_SIZE; i++)
    {
        theDeck.cards[i] = shuffled[i];
        theDeck.cards[i].used = false;
    }
}

void setUpFirstFoundationCard(deckType &theDeck, pileType foundations[])
{
    for (int i = 0; i < NUM_PILES; i++)
    {
        for (int j = 0; j < DECK_SIZE; j++)
        {
            if (theDeck.cards[j].face == foundations[i].cards[0].face)
            {
                foundations[i].cards[0] = theDeck.cards[j];
                theDeck.cards[j].used = true;
                break;
            }
        }
        foundations[i].topCard++;
        ;
        theDeck.remain--;
    }
}

int displayMenu(bool drawnCard, bool waste, bool noCards)
{
    int choice;
    std::cout << "What would you like to do: (Enter -1 to quit)" << std::endl;
    if (!drawnCard && !noCards)
    {
        std::cout << "1. Draw Card" << std::endl;
    }
    else if (drawnCard)
    {
        std::cout << "1. Play Drawn Card" << std::endl;
    }
    else if (noCards)
    {
        std::cout << "1. Finish Game and Calculate Score" << std::endl;
    }

    if (waste)
    {
        std::cout << "2. Play Card from Waste Pile" << std::endl;
        std::cout << "3. Display and Entire Waste Pile" << std::endl;
    }
    std::cin >> choice;
    if (choice == -1)
    {
        return choice;
    }
    while (!std::cin || choice < 1 || (waste && choice > 3) || (choice > 1 && !waste))
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is an invalid chocie" << std::endl;
        std::cin >> choice;
    }
    return choice;
}

void resetStream()
{
    std::cout << "You entered something that is not a number!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
