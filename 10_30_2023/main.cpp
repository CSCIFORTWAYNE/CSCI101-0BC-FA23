#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>

// lecture activity add code to read and get bill information for 3 more people

int main()
{
    /* int integer;
    double doubleNum;
    char character;
    std::string str;

    std::cout << "Enter an integer: ";
    std::cin >> integer;
    std::cout << "Enter a double: ";
    std::cin >> doubleNum;
    std::cout << "Enter a character: ";
    std::cin >> character;
    // std::cin.get(character);
    std::cout << "Enter something: ";
    std::cin >> std::ws;
    std::getline(std::cin, str);

    std::cout << integer << std::endl;
    std::cout << doubleNum << std::endl;
    std::cout << character << std::endl;
    std::cout << str << std::endl;
    std::cin >> std::ws;
    std::getline(std::cin, str);
    double squared = pow(integer, 2);
    double s = integer ^ 2; // this is not how we calcuate power
    std::cout << squared << std::endl; */
    std::ifstream namein;
    namein.open("names.txt");
    std::ofstream billOut;
    billOut.open("bills.txt");
    billOut << std::setprecision(2) << std::fixed << std::showpoint << std::left;
    double billAmount = 0;
    const double TIP_RATE = .2;
    const double TAX_RATE = .08;
    double tipAmount = 0;
    double taxAmount = 0;
    double total = 0;
    std::string name;
    std::cout << std::setprecision(2) << std::fixed << std::showpoint << std::left;
    // std::cout << "What is the name for the order? ";
    namein >> std::ws;
    std::getline(namein, name);
    std::cout << "What is the bill total for " << name << "? ";
    std::cin >> billAmount;
    taxAmount = billAmount * TAX_RATE;
    tipAmount = (billAmount + taxAmount) * TIP_RATE;
    total = billAmount + taxAmount + tipAmount;
    std::cout << "+" << std::setw(30) << std::setfill('-') << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+"
              << std::endl;
    std::cout << std::setfill(' ');
    std::cout << "|" << std::setw(30) << " Name"
              << "|" << std::setw(15) << " Bill Total"
              << "|" << std::setw(15) << " Tax Amount"
              << "|" << std::setw(15) << " Tip Amount"
              << "|" << std::setw(15) << " Total"
              << "|" << std::endl;
    std::cout << "+" << std::setw(30) << std::setfill('-') << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+"
              << std::endl;
    std::cout << std::setfill(' ');
    std::cout << "| " << std::setw(29) << name
              << "| $"
              << std::setw(13) << billAmount
              << "| $"
              << std::setw(13) << taxAmount
              << "| $"
              << std::setw(13) << tipAmount
              << "| $"
              << std::setw(13) << total
              << "|"
              << std::endl;
    std::cout << "+" << std::setw(30) << std::setfill('-') << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+"
              << std::endl;
    std::cout << std::setfill(' ');
    billOut << "+" << std::setw(30) << std::setfill('-') << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+"
            << std::endl;
    billOut << std::setfill(' ');
    billOut << "|" << std::setw(30) << " Name"
            << "|" << std::setw(15) << " Bill Total"
            << "|" << std::setw(15) << " Tax Amount"
            << "|" << std::setw(15) << " Tip Amount"
            << "|" << std::setw(15) << " Total"
            << "|" << std::endl;
    billOut << "+" << std::setw(30) << std::setfill('-') << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+"
            << std::endl;
    billOut << std::setfill(' ');
    billOut << "| " << std::setw(29) << name
            << "| $"
            << std::setw(13) << billAmount
            << "| $"
            << std::setw(13) << taxAmount
            << "| $"
            << std::setw(13) << tipAmount
            << "| $"
            << std::setw(13) << total
            << "|"
            << std::endl;
    billOut << "+" << std::setw(30) << std::setfill('-') << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+"
            << std::endl;
    billOut << std::setfill(' ');

    // next person in the file
    namein >> std::ws;
    std::getline(namein, name);
    std::cout << "What is the bill total for " << name << "? ";
    std::cin >> billAmount;
    taxAmount = billAmount * TAX_RATE;
    tipAmount = (billAmount + taxAmount) * TIP_RATE;
    total = billAmount + taxAmount + tipAmount;
    std::cout << "+" << std::setw(30) << std::setfill('-') << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+"
              << std::endl;
    std::cout << std::setfill(' ');

    std::cout << "| " << std::setw(29) << name
              << "| $"
              << std::setw(13) << billAmount
              << "| $"
              << std::setw(13) << taxAmount
              << "| $"
              << std::setw(13) << tipAmount
              << "| $"
              << std::setw(13) << total
              << "|"
              << std::endl;
    std::cout << "+" << std::setw(30) << std::setfill('-') << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+" << std::setw(15) << "-"
              << "+"
              << std::endl;
    billOut << std::setfill(' ');
    billOut << "| " << std::setw(29) << name
            << "| $"
            << std::setw(13) << billAmount
            << "| $"
            << std::setw(13) << taxAmount
            << "| $"
            << std::setw(13) << tipAmount
            << "| $"
            << std::setw(13) << total
            << "|"
            << std::endl;
    billOut << "+" << std::setw(30) << std::setfill('-') << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+" << std::setw(15) << "-"
            << "+"
            << std::endl;
    billOut << std::setfill(' ');
    // std::cout << "Bill total: $" << billAmount << std::endl;
    // std::cout << "20% Tip: $" << tipAmount << std::endl;

    return 0;
}