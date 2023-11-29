#include <iostream>
#include <limits>
#include <algorithm>
#include <fstream>

const int LIST_SIZE = 10;
const int NUM_SUITS = 4;

enum suitType
{
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
};
const suitType SUIT_LIST[NUM_SUITS] = {HEARTS,
                                       DIAMONDS,
                                       SPADES,
                                       CLUBS};
const std::string SUIT_NAMES[NUM_SUITS] = {"Hearts",
                                           "Diamonds",
                                           "Spades",
                                           "Clubs"};
const std::string SUIT_OUTPUT[NUM_SUITS] = {"Hearts  ♥",
                                            "Diamonds  ♦",
                                            "Spades  ♠",
                                            "Clubs  ♣"};

int inputInt(std::string prompt);
void resetStream();
void initialize(int list[], int listSize);
void seqSearch(const int list[], int listSize, int &foundPos, int searchItem);
void selectionSort(int list[], int listSize);
void initialize(suitType suitTable[][NUM_SUITS], int numRows, int numColumns);

// lecture activity fill in the following functions
void inputArray(int list[], int listSize);
void outputArray(int list[], int listSize);
void findLargest(int list[], int listSize, int &largestPos);
void calculateSum(int list[], int listSize, double &sum);

int main()
{
    int list[LIST_SIZE];
    double sum = 0;
    int largestPos = 0;
    initialize(list, LIST_SIZE);

    for (int i = 0; i < LIST_SIZE; i++)
    {
        list[i] = inputInt("Enter a number: ");
    }

    for (int i = 0; i < LIST_SIZE; i++)
    {
        std::cout << list[i] << std::endl;
    }
    for (int i = 0; i < LIST_SIZE; i++)
    {
        sum = sum + list[i];
    }

    std::cout << "The sum of the numbers is " << sum << " and the average is " << sum / 10.0 << std::endl;

    largestPos = 0;
    for (int i = 1; i < LIST_SIZE; i++)
    {
        if (list[largestPos] < list[i])
        {
            largestPos = i;
        }
    }

    std::cout << "The largest value is " << list[largestPos] << " at position " << largestPos << std::endl;
    int foundPos = 0;

    seqSearch(list, LIST_SIZE, foundPos, 73);
    if (foundPos == -1)
    {
        std::cout << "73 was not found in the list." << std::endl;
    }
    else
    {
        std::cout << "73 was found at position " << foundPos << std::endl;
    }

    suitType mySuit = DIAMONDS;
    std::cout << SUIT_OUTPUT[mySuit] << std::endl;

    selectionSort(list, LIST_SIZE);
    for (int i = 0; i < LIST_SIZE; i++)
    {
        std::cout << list[i] << std::endl;
    }

    std::string name = "Hello";
    std::string nameCpy = name;
    std::transform(nameCpy.begin(), nameCpy.end(), nameCpy.begin(), ::tolower);
    nameCpy = nameCpy + ".txt";
    std::ifstream inFile;
    inFile.open(nameCpy);
    if (!inFile.is_open())
        std::cout << "There is no file named " << nameCpy << std::endl;
    inFile.close();

    std::ofstream outFile;
    outFile.open(nameCpy);

    suitType mySuitTable[LIST_SIZE][NUM_SUITS];
    mySuitTable[4][2] = HEARTS;
    initialize(mySuitTable, LIST_SIZE, NUM_SUITS);

    int row = 2;
    for (int col = 0; col < NUM_SUITS; col++)
    {
        mySuitTable[row][col] = HEARTS;
    }
    int col = 1;
    for (row = 0; row < LIST_SIZE; row++)
    {
        mySuitTable[row][col] = DIAMONDS;
    }
    for (row = 0; row < LIST_SIZE; row++)
    {
        for (col = 0; col < NUM_SUITS; col++)
        {
            mySuitTable[row][col] = SUIT_LIST[col];
        }
    }

    return 0;
}

int inputInt(std::string prompt)
{
    int num;
    std::cout << prompt;
    std::cin >> num;
    while (!std::cin)
    {
        resetStream();
        std::cout << prompt;
        std::cin >> num;
    }

    return num;
}

void resetStream()
{
    std::cout << "You entered something that is not a number!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void initialize(int list[], int listSize)
{
    for (int i = 0; i < listSize; i++)
    {
        list[i] = 0;
    }
}

suitType getSuit(std::string prompt)
{
    suitType theSuit;
    int suitInt;
    std::cout << "Please choose a suit for " << prompt << ":" << std::endl;
    for (int i = 0; i < NUM_SUITS; i++)
    {
        std::cout << i + 1 << ". " << SUIT_NAMES[i] << std::endl;
    }
    std::cin >> suitInt;

    while (!std::cin || suitInt < 1 || suitInt > 4)
    {
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "Please choose a suit for " << prompt << ":" << std::endl;
        for (int i = 0; i < NUM_SUITS; i++)
        {
            std::cout << i + 1 << ". " << SUIT_NAMES[i] << std::endl;
        }
        std::cin >> suitInt;
    }
    theSuit = SUIT_LIST[suitInt - 1];
    return theSuit;
}

void seqSearch(const int list[], int listSize, int &foundPos, int searchItem)
{
    bool found = false;
    foundPos = -1;
    for (int i = 0; i < listSize && !found; i++)
    {
        if (searchItem == list[i])
        {
            foundPos = i;
            found = true;
        }
    }
}

void selectionSort(int list[], int listSize)
{
    int largestPos = 0;
    for (int unsorted = listSize; unsorted > 1; unsorted--)
    {
        findLargest(list, unsorted, largestPos);
        int temp = list[unsorted - 1];
        list[unsorted - 1] = list[largestPos];
        list[largestPos] = temp;
    }
}

void initialize(suitType suitTable[][NUM_SUITS], int numRows, int numColumns)
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numColumns; col++)
        {
            suitTable[row][col] = HEARTS;
        }
    }
}
