#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>

int getInt(std::string prompt);
char getByteUnits();
long convertByteUnits(char byteUnit);

// MAR is N bits where 2^N = number of memory cells = number of bytes.
int main()
{
    char byteUnit = getByteUnits();
    int mem = getInt("Enter the amount of memory: ");

    long memBytes = 0;
    memBytes = mem * convertByteUnits(byteUnit);

    std::cout << "The minimum MAR is ";
    std::cout << ceil(log2(memBytes)) << std::endl;
    return 0;
}

int getInt(std::string prompt)
{
    int inputNum;
    std::cout << prompt;
    std::cin >> inputNum;
    std::cout << std::endl;
    while (!std::cin || inputNum < 0)
    {
        if (!std::cin)
        {
            std::cout << "You entered something that is not a number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Please enter a positive number.";
        std::cout << prompt;
        std::cin >> inputNum;
        std::cout << std::endl;
    }
    return inputNum;
}

char getByteUnits()
{
    char byteUnit;
    std::cout << "Enter the prefix of the byte unit.\nB for bytes, K for KB, M for MB, G for GB, T for TB, P for PB, E for EB: ";
    std::cin >> byteUnit;
    std::cout << std::endl;
    byteUnit = toupper(byteUnit);
    while (byteUnit != 'B' && byteUnit != 'K' && byteUnit != 'M' && byteUnit != 'G' && byteUnit != 'T' && byteUnit != 'P' && byteUnit != 'E')
    {
        std::cout << "Enter the prefix of the byte unit.\nB for bytes, K for KB, M for MB, G for GB, T for TB, P for PB, E for EB: ";
        std::cin >> byteUnit;
        std::cout << std::endl;
        byteUnit = toupper(byteUnit);
    }

    return byteUnit;
}

long convertByteUnits(char byteUnit)
{
    long bytes = 0;
    switch (byteUnit)
    {
    case 'B':
        bytes = 1;
        break;
    case 'K':
        bytes = pow(2, 10);
        break;
    case 'M':
        bytes = pow(2, 20);
        break;
    case 'G':
        bytes = pow(2, 30);
        break;
    case 'T':
        bytes = pow(2, 40);
        break;
    case 'P':
        bytes = pow(2, 50);
        break;
    case 'E':
        bytes = pow(2, 60);
        break;
    default:
        std::cout << "The byte unit is invalid." << std::endl;
        bytes = 0;
    }

    return bytes;
}