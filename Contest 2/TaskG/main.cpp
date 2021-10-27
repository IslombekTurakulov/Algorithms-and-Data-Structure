#include <iostream>
#include <vector>

long long lcm(long long a, long long b);

long long nod(long long a, long long b);

std::string gcd(const std::vector<long long> &num) {
    // Дальше идут проверки на размерность.
    if (num.size() == 0) {
        return 0;
    }
    if (num.size() == 1) {
        return std::to_string(num[0]);
    }

    // Вызываем первый раз функцию для инициализации res
    long long res = lcm(num[0], num[1]);

    // Через цикл for просто пробегаемся по числам с подсчётом функций.
    for (auto i = 2; i < num.size(); i++) {
        res = lcm(res, num[i]);
    }

    // Присваиваем результат и число функций как строку.
    std::string result = std::to_string(res);
    return result;
}

int main() { // ТОЧКА ВХОДА
    long long amountOfNumbers = 0;
    std::cin >> amountOfNumbers;
    // Создаём вектор из long long.
    std::vector<long long> arrayNumbers(amountOfNumbers);
    // Цикл позволяет брать входные данные с проверкой на вещественное число.
    for (int i = 0; i < amountOfNumbers; ++i) {
        std::string tempInput;
        std::cin >> tempInput;
        if (tempInput.find('.') < tempInput.length()){
            std::cout << "Sequence has float values!";
            return 0;
        }
        arrayNumbers[i] = static_cast<long long>(std::llabs(std::stoll(tempInput)));
    }
    // Вызывается кастомная функция gcd
    std::cout << gcd(arrayNumbers);
    return 0;
}

// Метод nod помогает вычислить наибольший общий делитель двух чисел
// countOfFunctions считает, сколько было произведено операций во время исполнения цикла while.
long long nod(long long a, long long b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Ну это НОК, держу в курсе))
long long lcm(long long a, long long b) {
    return (a * b) / nod(a, b);
}