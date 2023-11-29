#include <iostream>
#include <limits>

int inputInt(std::string prompt);
void resetStream();

int main()
{
    int list[10];
    double sum = 0;
    int largestPos = 0;
    for (int i = 0; i < 10; i++)
    {
        list[i] = 0;
    }

    for (int i = 0; i < 10; i++)
    {
        list[i] = inputInt("Enter a number: ");
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout << list[i] << std::endl;
    }
    for (int i = 0; i < 10; i++)
    {
        sum = sum + list[i];
    }

    std::cout << "The sum of the numbers is " << sum << " and the average is " << sum / 10.0 << std::endl;

    largestPos = 0;
    for (int i = 1; i < 10; i++)
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