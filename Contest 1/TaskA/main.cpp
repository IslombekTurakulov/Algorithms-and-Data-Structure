// TaskA.cpp

#include <iostream>

int main()
{
    //double averageNumber;
    int inNumbers;
    int howManyNumbers = 0;
    int totalSumNumbers = 0;

    std::cin >> inNumbers;
    while (inNumbers != 0)
    {
        totalSumNumbers += inNumbers;
        std::cin >> inNumbers;
        ++howManyNumbers;
    }
    std::cout << (double)totalSumNumbers / howManyNumbers;


}