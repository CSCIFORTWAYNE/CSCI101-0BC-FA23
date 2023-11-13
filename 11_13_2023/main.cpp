#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <cctype>
#include <ctime>

int main()
{
    // lecture activity part 1 convert the while loop below to a for loop.
    /* int i = 0;
    while (i < 20)
    {
        std::cout << i << " ";
        i++; // i = i + 1;
    }
    std::cout << std::endl; */
    int i;
    for (i = 0; i <= 20; i = i + 5)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    double calories = 0;
    double sum = 0;
    int count = 0;
    std::ifstream caloriesFile;
    caloriesFile.open("calories.txt");
    while (!caloriesFile.eof())
    {
        caloriesFile >> calories;
        if (caloriesFile)
        {
            sum += calories; // sum = sum + calories;
            count++;
        }
    }
    if (std::cin.eof())
        return 0;

    /*  char cont = 'Y';
     std::cout << "Do you want to enter calories burned? ";
     std::cin >> cont;
     std::cout << std::endl;
     cont = toupper(cont);
     while(cont != 'Y' && cont != 'N')
     {
        std::cout << "Please enter Y or N." << std::endl;
        std::cin >> cont;
        std::cout << std::endl;
        cont = toupper(cont);
     }
     while (cont == 'Y')
     {
         std::cout << "Enter the number of calories burned: ";
         std::cin >> calories;
         std::cout << std::endl;
         while (!std::cin || calories < 0)
         {
             if (!std::cin)
             {
                 std::cout << "You entered something that is not a number!" << std::endl;
                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             }
             std::cout << "The number of calories should be greater than 0." << std::endl;
             std::cout << "Enter the number of calories burned: ";
             std::cin >> calories;
             std::cout << std::endl;
         }

         sum += calories; // sum = sum + calories;
         count++;

         std::cout << "Do you want to enter another day? ";
         std::cin >> cont;
         std::cout << std::endl;
         cont = toupper(cont);
         while(cont != 'Y' && cont != 'N')
         {
           std::cout << "Please enter Y or N." << std::endl;
           std::cin >> cont;
           std::cout << std::endl;
           cont = toupper(cont);
         }

     } */
    if (count > 0)
        std::cout << "The average calories burned is " << sum / count << std::endl;

    int secret = 0;
    int guess = 0;
    srand(time(0));

    secret = rand() % 100 + 1;
    bool isGuessed = false;

    while (!isGuessed)
    {
        std::cout << "Enter a number between 1 and 100: ";
        std::cin >> guess;
        std::cout << std::endl;
        while (!std::cin || guess < 1 || guess > 100)
        {
            if (!std::cin)
            {
                std::cout << "You entered something that is not a number!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Please enter a number between 1 and 100: ";
            std::cin >> guess;
            std::cout << std::endl;
        }

        isGuessed = secret == guess;
        if (secret > guess)
        {
            std::cout << "Your guess is too low. Guess again!" << std::endl;
        }
        else if (secret < guess)
        {
            std::cout << "Your guess is too high. Guess again!" << std::endl;
        }
    }
    std::cout << "Congrats! You guessed the number." << std::endl;

    return 0;
}