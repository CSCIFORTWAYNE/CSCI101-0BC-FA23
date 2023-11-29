#include <iostream>
#include <limits>

const int LIST_SIZE = 10;

int inputInt(std::string prompt);
void resetStream();
void initialize(int list[], int listSize);
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
