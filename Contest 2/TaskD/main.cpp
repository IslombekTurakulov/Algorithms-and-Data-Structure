#include <iostream>
#include <cstring>

int main() {
    int parties = 0;
    int ballots = 0;
    std::cin >> parties;
    std::cin >> ballots;

    int ballotsOfParties[parties];
    int correctBallots = 0;
    // Инициализирует массив
    memset(ballotsOfParties, 0, sizeof(ballotsOfParties));
    while (ballots-- > 0) {
        std::string ballot;
        std::cin >> ballot;
        int counter = 0;
        int index = 0;
        bool isCorrectOrNot = true;
        // Я думаю тут очевидно, что происходит.
        for (char letter : ballot) {
            // Если символ плюс, добавляем одно очко, иначе ничего.
            if (letter == '+') {
                counter += 1;
            } else {
                counter += 0;
            }
            // Если очко не равно единице, прибавляем с индексу единицу, иначе ничего.
            if (counter != 1) {
                index += 1;
            } else {
                index += 0;
            }
            // Если считыватель больше единицы, тогда строка является некорректной.
            if (counter > 1){
                isCorrectOrNot = false;
                break;
            }
        }
        if (isCorrectOrNot && counter == 1){
            correctBallots++;
            ballotsOfParties[index]++;
        }
    }

    for (int indexParty = 0; indexParty < parties; ++indexParty) {
        // Проверка на проход в парламент.
        if (ballotsOfParties[indexParty] * 1.0 / correctBallots > 0.069){
            std::cout << indexParty + 1 << " ";
        }
    }

}
