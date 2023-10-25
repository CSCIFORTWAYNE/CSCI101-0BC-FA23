#include <iostream>

int main()
{
    double billAmount = 0;
    double billAmountCpy = 0;

    billAmount = 38.95;

    billAmountCpy = billAmount;

    const double TIP_RATE = .2; // tipRate = .2;

    billAmount = 45.92;

    int x = 7;
    int y = 2;
    std::cout << x / y << std::endl;
    std::cout << x % y << std::endl;

    return 0;
}