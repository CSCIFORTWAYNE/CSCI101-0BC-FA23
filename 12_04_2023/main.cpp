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
enum choiceType
{
    DRAW,
    PLAYDRAW,
    FINISH,
    PLAYWASTE,
    DISPLAY
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
choiceType displayMenu(bool drawnCard, bool waste, bool noCards);
void drawCard(deckType &theDeck);
void playDrawnCard(deckType &theDeck, pileType foundations[], pileType wastes[], bool &drawnCard);
void playFoundation(deckType &theDeck, pileType &foundation, bool &drawnCard);
void playFromWaste(pileType foundations[], pileType wastes[]);
void displayWaste(pileType &wastePile);
int chooseWaste();
int calculateScore(deckType &theDeck, pileType wastes[]);
void resetStream();
void processChoice(bool &drawn, choiceType choice, deckType &theDeck, pileType foundations[], pileType wastes[], bool &finished);

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
    choiceType choice;
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
        processChoice(drawnCard, choice, gameDeck, foundations, wastePiles, finished);
    }
    int score = calculateScore(gameDeck, wastePiles);
    if (score == 0)
    {
        std::cout << "You won! You scored 0 points." << std::endl;
    }
    else
    {
        std::cout << "Game Over! You scored " << score << " points." << std::endl;
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
        output << "  ┌─────────┐  ";
    }
    output << std::endl
           << " ";
    for (int i = 0; i < numPiles; i++)
    {
        output << std::setfill(' ') << std::left;
        output << " │ " << std::setw(8);
        if (piles[i].topCard > -1)
        {
            output << faceStr[piles[i].cards[piles[i].topCard].face];
        }
        else
        {
            output << " ";
        }
        output << "│   ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << "  │" << std::setw(9) << " "
               << "│  ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << std::right;
        output << "  │";
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
               << "│  ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << "  │" << std::setw(9) << " "
               << "│  ";
    }
    output << std::endl;
    for (int i = 0; i < numPiles; i++)
    {
        output << "  │" << std::setw(8);
        if (piles[i].topCard > -1)
        {
            output << faceStr[piles[i].cards[piles[i].topCard].face];
        }
        else
        {
            output << " ";
        }
        output << " │  ";
    }
    output << std::endl;

    for (int i = 0; i < numPiles; i++)
    {
        output << i + 1 << " └─────────┘  ";
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

choiceType displayMenu(bool drawnCard, bool waste, bool noCards)
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
        return FINISH;
    }
    while (!std::cin || choice < 1 || (waste && choice > 3) || (choice > 1 && !waste))
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is an invalid choice" << std::endl;
        std::cin >> choice;
    }
    if (!drawnCard && choice == 1 && !noCards)
    {
        return DRAW;
    }
    else if (choice == 1 && drawnCard)
    {
        return PLAYDRAW;
    }
    else if (choice == 1 && noCards)
    {
        return FINISH;
    }
    else if (choice == 2)
    {
        return PLAYWASTE;
    }
    else if (choice == 3)
    {
        return DISPLAY;
    }
    return FINISH;
}

void drawCard(deckType &theDeck)
{
    do
    {
        theDeck.next++;
    } while (theDeck.cards[theDeck.next].used);
    theDeck.remain--;
}

void playDrawnCard(deckType &theDeck, pileType foundations[], pileType wastes[], bool &drawnCard)
{
    char typeOfPile;
    int p;
    std::cout << "Do you want ot play on a: " << std::endl;
    std::cout << "F. Foundation Pile" << std::endl;
    std::cout << "W. Waste Pile" << std::endl;
    std::cin >> typeOfPile;
    typeOfPile = toupper(typeOfPile);
    while (typeOfPile != 'F' && typeOfPile != 'W')
    {
        std::cout << "I do not understand. I am expecting F or W." << std::endl;
        std::cout << "Do you want to play on a:" << std::endl;
        std::cout << "F. Foundation Pile" << std::endl;
        std::cout << "W. Waste Pile" << std::endl;
        std::cin >> typeOfPile;
        typeOfPile = toupper(typeOfPile);
    }
    std::string pileTypeString = typeOfPile == 'F' ? "foundation" : "waste";
    std::cout << "Which " << pileTypeString << " pile (1-4) do you want to play on? ";
    std::cin >> p;
    std::cout << std::endl;
    while (!std::cin || p < 1 || p > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid " << pileTypeString << " pile." << std::endl;
        std::cout << "Which " << pileTypeString << " pile (1-4) do you want to play on? ";
        std::cin >> p;
        std::cout << std::endl;
    }
    if (typeOfPile == 'F')
    {
        playFoundation(theDeck, foundations[p - 1], drawnCard);
    }
    else
    {
        // play on the waste pile chosen
        wastes[p - 1].cards[wastes[p - 1].topCard + 1] = theDeck.cards[theDeck.next];
        wastes[p - 1].topCard++;
        theDeck.cards[theDeck.next].used = true;
        drawnCard = false;
    }
}

void playFoundation(deckType &theDeck, pileType &foundation, bool &drawnCard)
{
    if (foundation.cards[foundation.topCard + 1].face == theDeck.cards[theDeck.next].face)
    {
        foundation.cards[foundation.topCard + 1] = theDeck.cards[theDeck.next];
        theDeck.cards[theDeck.next].used = true;
        foundation.topCard++;
        drawnCard = false;
    }
    else
    {
        std::cout << "That is an invalid play. The next card for that pile is a ";
        std::cout << faceStr[foundation.cards[foundation.topCard + 1].face] << std::endl;
    }
}

void playFromWaste(pileType foundations[], pileType wastes[])
{
    int wastePileNum;
    int foundPileNum;
    std::cout << "Which waste pile (1-4) do you want to play from? ";
    std::cin >> wastePileNum;
    while (!std::cin || wastePileNum < 1 || wastePileNum > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid waste pile." << std::endl;
        std::cout << "Which waste pile (1-4) do you want to play from? ";
        std::cin >> wastePileNum;
    }
    std::cout << "Which foundation pile (1-4) do you want to play on? ";
    std::cin >> foundPileNum;
    while (!std::cin || foundPileNum < 1 || foundPileNum > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid foundation pile." << std::endl;
        std::cout << "Which foundation pile (1-4) do you want to play on? ";
        std::cin >> foundPileNum;
    }
    if (foundations[foundPileNum - 1].cards[foundations[foundPileNum - 1].topCard + 1].face == wastes[wastePileNum - 1].cards[wastes[wastePileNum - 1].topCard].face)
    {
        foundations[foundPileNum - 1].cards[foundations[foundPileNum - 1].topCard + 1] = wastes[wastePileNum - 1].cards[wastes[wastePileNum - 1].topCard];
        foundations[foundPileNum - 1].topCard++;
        wastes[wastePileNum - 1].topCard--;
    }
    else
    {
        std::cout << "That is an invalid play. The next card for that pile is a ";
        std::cout << faceStr[foundations[foundPileNum - 1].cards[foundations[foundPileNum - 1].topCard + 1].face] << std::endl;
    }
}

void displayWaste(pileType &wastePile)
{
    for (int i = wastePile.topCard; i >= 0; i--)
    {
        std::cout << printASCIICard(wastePile.cards[i]) << std::endl;
    }
}

int chooseWaste()
{
    int wastePileNum;
    std::cout << "Which waste pile (1-4) do you want to see? ";
    std::cin >> wastePileNum;
    while (!std::cin || wastePileNum < 1 || wastePileNum > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "That is not a valid waste pile." << std::endl;
        std::cout << "Which waste pile (1-4) do you want to see? ";
        std::cin >> wastePileNum;
    }
    return wastePileNum - 1;
}

int calculateScore(deckType &theDeck, pileType wastes[])
{
    int score = 0;
    for (int i = 0; i < NUM_PILES; i++)
    {
        score += wastes[i].topCard + 1;
    }
    score += theDeck.remain;
    return score;
}

void resetStream()
{
    std::cout << "You entered something that is not a number!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void processChoice(bool &drawn, choiceType choice, deckType &theDeck, pileType foundations[], pileType wastes[], bool &finished)
{

    switch (choice)
    {
    case DRAW:
        drawCard(theDeck);
        drawn = true;
        break;
    case PLAYDRAW:
        playDrawnCard(theDeck, foundations, wastes, drawn);
        break;
    case PLAYWASTE:
        playFromWaste(foundations, wastes);
        break;
    case DISPLAY:
    {
        int wastePileNum = chooseWaste();
        displayWaste(wastes[wastePileNum]);
        break;
    }
    case FINISH:
        finished = true;
    }
}
