#include <iostream>
#include <string>

int main()
{
    double billAmount = 0;
    double billAmountCpy = 0;
    std::string name;

    billAmount = 38.95;

    billAmountCpy = billAmount;

    const double TIP_RATE = .2; // tipRate = .2;

    billAmount = 45.92;
    std::cout << "Enter the bill amount: ";
    std::cin >> billAmount;

    int x = 7;
    int y = 2;
    std::cout << static_cast<double>(x) / y << std::endl;
    std::cout << x % y << std::endl;

    double tip = billAmount * TIP_RATE;
    std::cout << "The 20% tip for bill amount $" << billAmount << " is $" << tip << std::endl;

    return 0;
}