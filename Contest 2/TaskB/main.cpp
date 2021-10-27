#include <iostream>

int main()
{
    // int count - для счёта кол-ва выполненных циклов.
    int count;
    // Индекс для дальнейшего сравнения с вводом от пользователя.
    int index = 1;
    // input - выступает как n в условии.
    int input;
    std::cin >> input;
    // Цикл while используется для подсчёта количества действий для достижения переменной input a.k.a n
    while(input > index) {
        index *= 2;
        count++;
    }
    std::cout << count;
    return 0;
}
