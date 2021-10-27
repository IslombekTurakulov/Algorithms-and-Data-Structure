#include <iostream>
#include <string>

void Verification(const std::string &input);

int main() // Точка входа
{
    std::string input;
    std::cin >> input;

    // Метод проверки.
    Verification(input);

    return 0;
}

void Verification(const std::string &input) {
    // Объявляем и инициализируем переменные bool типа.
    bool isUpperLetter = false;
    bool isLetterDigit = false;
    bool isLowerLetter = false;

    if (input.length() >= 8) {
        // Прогоняюсь через символы в слове.
        for(char letter : input) {
            // Проверка на цифры.
            if (isdigit(letter) && !isLetterDigit) {
                isLetterDigit = true;
            }
            // Проверка на заглавную букву.
            else if (isupper(letter) && !isUpperLetter) {
                isUpperLetter = true;
            }
            // Проверка на строчную букву.
            else if (islower(letter) && !isLowerLetter) {
                isLowerLetter = true;
            }
        }
        // Если булевские переменные удовлетворяют значению, выводит "YES", иначе "NO".
        std::cout << (isLowerLetter && isUpperLetter && isLetterDigit ? "YES" : "NO");
    }
    else{
        std::cout << "NO";
    }
}

