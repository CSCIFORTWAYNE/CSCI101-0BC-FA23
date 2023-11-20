#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>
#include <algorithm>

int getInt(std::string prompt);
char getByteUnits();
long convertByteUnits(char byteUnit);
int secret(int x);
void resetStream();
void convert2dMemory(int mar, int &marC, int &marR);
void calculateDimensions(int marC, int marR, int &memSizeR, int &memSizeC, char &byteUnit);

// MAR is N bits where 2^N = number of memory cells = number of bytes.
int main()
{
    char byteUnit = getByteUnits();
    int mem = getInt("Enter the amount of memory: ");

    long memBytes = 0;
    memBytes = mem * convertByteUnits(byteUnit);
    int mar = ceil(log2(memBytes));
    std::cout << "The minimum MAR is ";
    std::cout << mar << std::endl;
    int columnMar = 0;
    int rowMar = 0;
    convert2dMemory(mar, columnMar, rowMar);
    int columnMem = 0;
    int rowMem = 0;
    calculateDimensions(columnMar, rowMar, rowMem, columnMem, byteUnit);
    std::cout << "The 2d memory would have: " << std::endl;
    std::cout << " bits sent to the row decoder and "
              << " bits sent to the column decoder." << std::endl; // add to this line the values sent to the row and column decoder
    std::cout << "The dimensions of the memory are: ";
    std::cout << rowMem;
    if (byteUnit == 'B')
    {
        std::cout << " bytes";
    }
    else
    {
        std::cout << " " << byteUnit << "B";
    }
    std::cout << " x " << columnMem;
    if (byteUnit == 'B')
    {
        std::cout << " bytes";
    }
    else
    {
        std::cout << " " << byteUnit << "B";
    }
    std::cout << std::endl;

    // int y = secret(3);
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
            resetStream();
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

int secret(int x)
{
    if (x > 5)
        return 2 * x;
    return x;
}

void resetStream()
{
    std::cout << "You entered something that is not a number!" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void convert2dMemory(int mar, int &marC, int &marR)
{
    std::string square;
    if (mar % 2 != 0)
    {
        std::cout << "The MAR is odd. Do you want the 2d memory to be square or rectangular? ";
        std::cin >> std::ws;
        std::cin >> square;
        std::cout << std::endl;
        std::string squareCpy = square;
        std::transform(squareCpy.begin(), squareCpy.end(), squareCpy.begin(), ::toupper);
        while (squareCpy != "SQUARE" && squareCpy != "RECTANGULAR")
        {
            std::cout << "I don't understand. Do you want memory to be square or rectangular? ";
            std::cin >> square;
            std::cout << std::endl;
            squareCpy = square;
            std::transform(squareCpy.begin(), squareCpy.end(), squareCpy.begin(), ::toupper);
        }
        if (squareCpy == "SQUARE")
        {
            mar = mar + 1;
        }
        else
        {
            marR = mar / 2;
            marC = mar / 2 + 1;
            return;
        }
    }
    marR = mar / 2;
    marC = mar / 2;
}

void calculateDimensions(int marC, int marR, int &memSizeR, int &memSizeC, char &byteUnit)
{
    if (marR >= 60)
    {
        byteUnit = 'E';
        memSizeR = pow(2, (marR - 60));
        memSizeC = pow(2, (marC - 60));
    }
    else if (marR >= 50)
    {
        byteUnit = 'P';
        memSizeR = pow(2, (marR - 50));
        memSizeC = pow(2, (marC - 50));
    }
    else if (marR >= 40)
    {
        byteUnit = 'T';
        memSizeR = pow(2, (marR - 40));
        memSizeC = pow(2, (marC - 40));
    }
    else if (marR >= 30)
    {
        byteUnit = 'G';
        memSizeR = pow(2, (marR - 30));
        memSizeC = pow(2, (marC - 30));
    }
    else if (marR >= 20)
    {
        byteUnit = 'M';
        memSizeR = pow(2, (marR - 20));
        memSizeC = pow(2, (marC - 20));
    }
    else if (marR >= 10)
    {
        byteUnit = 'K';
        memSizeR = pow(2, (marR - 10));
        memSizeC = pow(2, (marC - 10));
    }
    else
    {
        byteUnit = 'B';
        memSizeR = pow(2, (marR));
        memSizeC = pow(2, (marC));
    }
}