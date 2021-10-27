#include <iostream>
#include <vector>

long long nod(long long a, long long b, long long &countOfFunctions);

std::string gcd(const std::vector<long long> &num) {
    // Создаём переменную для подсчёта функций.
    long long countOfFunctions = 1;
    // Дальше идут проверки на размерность.
    if (num.size() == 0) {
        return 0;
    }
    if (num.size() == 1) {
        return reinterpret_cast<const char *>(num[0]);
    }
    // Вызываем первый раз функцию для инициализации res
    long long res = nod(num[1], num[0], countOfFunctions);

    // Через цикл for просто пробегаемся по числам с подсчётом функций.
    for (auto i = 2; i < num.size(); i++) {
        res = nod(num[i], res, countOfFunctions);
        countOfFunctions++;
    }
    // Присваиваем результат и число функций как строку.
    std::string result = std::to_string(res) + " " + std::to_string(countOfFunctions);
    return result;
}

int main() { // ТОЧКА ВХОДА
    int amountOfNumbers = 0;
    std::cin >> amountOfNumbers;
    // Создаём вектор из long long.
    std::vector<long long> arrayNumbers(amountOfNumbers);
    // Цикл позволяет брать входные данные с проверкой на вещественное число.
    for (int i = 0; i < amountOfNumbers; ++i) {
        double tempInput;
        std::cin >> tempInput;
        if (tempInput != (int) tempInput) {
            std::cout << "Sequence has float values!";
            return 0;
        }
        arrayNumbers[i] = tempInput;
    }
    // Вызывается кастомная функция gcd
    std::cout << gcd(arrayNumbers);
    return 0;
}

// Метод nod помогает вычислить наибольший общий делитель двух чисел
// countOfFunctions считает, сколько было произведено операций во время исполнения цикла while.
long long nod(long long a, long long b, long long &countOfFunctions) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
        countOfFunctions++;
    }
    return a;
}