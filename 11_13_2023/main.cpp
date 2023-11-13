#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    /* int i = 0;
    while (i < 20)
    {
        std::cout << i << " ";
        i++; // i = i + 1;
    }
    std::cout << std::endl; */
    double calories = 0;
    double sum = 0;
    int count = 0;
    char cont = 'Y';
    std::cout << "Do you want to enter calories burned? ";
    std::cin >> cont;
    std::cout << std::endl;
    while (cont == 'Y')
    {
        std::cout << "Enter the number of calories burned: ";
        std::cin >> calories;
        std::cout << std::endl;

        sum += calories; // sum = sum + calories;
        count++;

        std::cout << "Do you want to enter another day? ";
        std::cin >> cont;
        std::cout << std::endl;
    }

    std::cout << "The average calories burned is " << sum / count << std::endl;

    return 0;
}