// TaskBC++.cpp

#include <iostream>


double MathPow(double firstNumber, int secondNumber)
{
    if (secondNumber != 0 && secondNumber % 2 == 0)
        return MathPow(firstNumber * firstNumber, secondNumber / 2);
    if (secondNumber == 0)
        return 1;
    return firstNumber * MathPow(firstNumber, secondNumber - 1);
}

int main()
{
    double firstNumber;
    int secondNumber;

    std::cin >> firstNumber;
    std::cin >> secondNumber;
    std::cout << MathPow(firstNumber, secondNumber);
}