#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;

void showResult(string result) {
    for (char letter : result) {
        cout << letter << " ";
    }
}

string getCompare(const string *f_input, const string *s_input,
                   char index, int f_pos, int s_pos) {
    string result;
    int f_length = (*f_input).length();
    int s_length = (*s_input).length();
    // Если у первой позиции есть буква, у второй нет, добавляем букву в result
    // и наоборот.
    if ((f_pos >= 0 && f_pos < f_length) &&
        (s_pos < 0 || s_pos > s_length)) {
        result += index;
    }
    if ((s_pos >= 0 && s_pos < s_length) &&
        (f_pos < 0 || f_pos > f_length)) {
        result += index;
    }
    return result;
}

string getLetters(string *f_input,
                  string *s_input) {
    string result = "";
    for (char index = 'a'; index < 'z'; ++index) {
        int f_pos = (*f_input).find(index);
        int s_pos = (*s_input).find(index);
        // Если оба индекса неверные или правильные продолжаем цикл.
        if (f_pos < 0 || f_pos >= (*f_input).length()
            || s_pos < 0 || s_pos >= (*s_input).length()) {
            result += getCompare(f_input, s_input, index, f_pos, s_pos);
        }
    }
    return result;
}


int main() {
    string first_input;
    string second_input;

    getline(std::cin, first_input);
    getline(std::cin, second_input);

    string result = getLetters(&first_input, &second_input);
    if (!result.empty()) {
        showResult(result);
    } else {
        cout << "NONE";
    }
    return 0;
}
