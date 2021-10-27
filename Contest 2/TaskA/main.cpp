#include <iostream>
#include <string>


bool isPalindrome(std::string inputWord);

int main() {
    std::string inputWord;
    std::cin >> inputWord;
    std::cout << (isPalindrome(inputWord) ? "YES" : "NO");
    return 0;
}

bool isPalindrome(std::string inputWord) {
    // Создадим временную строку для добавления согласных букв с inputWord
    std::string tempWord;
    // Если буква принадлежит гласным, цикл продолжается, если нет, то добавляется
    // в tempWord.
    // Например: dream , после цикла у переменной tempWord будет drm
    for (int i = 0; i < inputWord.length(); ++i) {
        // Создадим временную переменную буквы, чтобы было легче сравнивать.
        char tempLetter = tolower(inputWord[i]);
        if ('u' == tempLetter || tempLetter == 'a'
            || tempLetter == 'o')
            continue;
        if (tempLetter == 'e' || tempLetter == 'i')
            continue;
        tempWord += tempLetter;
    }
    // Пробежимся через цикл for для проверки слова.
    for (int i = 0; i < tempWord.length() / 2; i++) {
        // Проверка на палиндром.
        // tolower переводит символ в нижний регистр, чтобы проверка была не чувствительна к регистру.
        if (tolower(tempWord[i]) != tolower(tempWord[(tempWord.length() - i - 1)])) {
            return false;
        }
    }
    return true;
}