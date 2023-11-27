#include <iostream>
#include <string>
#include <limits>

const int NUM = 145;

enum suitType
{
    HEARTS = 8,
    DIAMONDS = 15,
    SPADES = 23,
    CLUBS = 29
};
/* const int HEARTS = 0;
const int DIAMONDS = 1;
const int SPADES = 2;
const int CLUBS = 3; */
void myFunc(int x);
void resetStream();
suitType getSuit(std::string prompt);
std::string printSuit(suitType theSuit);
void displaySuitList();
suitType inputToSuitType(int suitInput);

int main()
{

    suitType x = getSuit("x");
    suitType y = SPADES;
    int num = 45;
    /* if (true)
    {
        x = CLUBS;
    } */
    // std::cin >> x;
    std::cout << x << std::endl;            // prints the numeric enum value
    std::cout << printSuit(x) << std::endl; // prints the string version
    return 0;
}

void myFunc(int x)
{
    x = 7;
}

suitType getSuit(std::string prompt)
{
    suitType theSuit;
    int suitInt;
    std::cout << "Please choose a suit for " << prompt << ":" << std::endl;
    displaySuitList();
    std::cin >> suitInt;

    while (!std::cin || suitInt < 1 || suitInt > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "Please choose a suit for " << prompt << ":" << std::endl;
        displaySuitList();
        std::cin >> suitInt;
    }
    theSuit = inputToSuitType(suitInt);
    return theSuit;
}

std::string printSuit(suitType theSuit)
{
    std::string suitStr = "";
    switch (theSuit)
    {
    case CLUBS:
        suitStr = "Clubs ♣";
        break;
    case HEARTS:
        suitStr = "Hearts ♥";
        break;
    case SPADES:
        suitStr = "Spades ♠";
        break;
    case DIAMONDS:
        suitStr = "Diamonds ♦";
        break;
    default:
        suitStr = "Unknown Suit";
    }
    return suitStr;
}

void displaySuitList()
{
    std::cout << "1. Hearts" << std::endl;
    std::cout << "2. Diamonds" << std::endl;
    std::cout << "3. Clubs" << std::endl;
    std::cout << "4. Spades" << std::endl;
}

suitType inputToSuitType(int suitInput)
{
    suitType theSuit = HEARTS;
    switch (suitInput)
    {
    case 1:
        theSuit = HEARTS;
        break;
    case 2:
        theSuit = DIAMONDS;
        break;
    case 3:
        theSuit = CLUBS;
        break;
    case 4:
        theSuit = SPADES;
        break;
    default:
        theSuit = HEARTS;
    }
    return theSuit;
}

void resetStream()
{
    std::cout << "You entered something that is not a number!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
