#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#define NDEBUG
#include <cassert>

int main()
{
    int myNum = 93;
    int yourNum = 0;
    std::cout << "Enter a number between 1 and 100: ";
    std::cin >> yourNum;
    std::cout << std::endl;
    assert(std::cin);
    if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        return 0;
    }
    if (yourNum < 1 || yourNum > 100)
    {
        std::cout << "You did not enter a number between 1 and 100!" << std::endl;
        return 0;
    }

    std::string day;
    std::cout << "What day is it? ";
    std::cin >> day;
    std::cout << std::endl;
    std::transform(day.begin(), day.end(), day.begin(), ::tolower);

    if (myNum >= yourNum || day == "monday")
    {

        std::cout << "My number is bigger. I win!!!!" << std::endl;
        std::cout << "I'm still in the true block" << std::endl;
        day = "Friday";
        myNum + yourNum;
    }
    else
    {
        std::cout << "Your number was bigger." << std::endl;
    }
    std::cout << "Thanks for playing." << std::endl;

    /*  if (0)
         std::cout << "if(0) is true" << std::endl;
     else
         std::cout << "if(0) is false" << std::endl;*/

    int score = 0;
    std::cout << "Enter a score: ";
    std::cin >> score;
    std::cout << std::endl;
    if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        return 0;
    }
    if (score < 1 || score > 100)
    {
        std::cout << "You did not enter a number between 1 and 100!" << std::endl;
        return 0;
    }

    if (score >= 90)
    {
        std::cout << "The grade is A." << std::endl;
    }
    else if (score >= 80)
    {
        std::cout << "The grade is B." << std::endl;
    }
    else if (score >= 70)
    {
        std::cout << "The grade is C." << std::endl;
    }
    else if (score >= 60)
    {
        std::cout << "The grade is D." << std::endl;
    }
    else
        std::cout << "The grade is F." << std::endl;

    bool x = 1.0 == 3.0 / 7.0 + 2.0 / 7.0 + 2.0 / 7.0;

    // fix the block of code below for the lecture activity
    /*     int num;
        std::cout << "Enter an integer: ";
        std::cin >> num;
        std::cout << std::endl;
        if (0 <= num <= 10)
            std::cout << num << " is within 0 and 10." << std::endl;
        else
            std::cout << num << " is not within 0 and 10." << std::endl;
     */
    return 0;
}