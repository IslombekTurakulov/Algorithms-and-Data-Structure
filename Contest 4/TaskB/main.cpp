#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

void addPlusOrMinus(const int length_min, const string &old_str,
                    const string &pluses_and_minuses,
                    string *pluses_and_minuses_new) {
    for (int i = 0; i < length_min; ++i) {
        if (old_str[i] == '+') {
            *pluses_and_minuses_new += "+";
        } else if (pluses_and_minuses[i] != '+') {
            *pluses_and_minuses_new += "-";
        } else {
            *pluses_and_minuses_new += "+";
        }
    }
}

string getSymbols(const string &old_str, const string &pluses_and_minuses) {
    string pluses_and_minuses_new;
    int length_min;

    // Тоже очевидно происходящее
    if (old_str.length() >= pluses_and_minuses.length()) {
        length_min = pluses_and_minuses.length();
    } else {
        length_min = old_str.length();
    }
    // Метод для того, чтобы найти символ плюс или минус.
    addPlusOrMinus(length_min, old_str, pluses_and_minuses, &pluses_and_minuses_new);

    // Думаю тут очевидно что происходит
    for (int i = length_min; i < old_str.length(); ++i) {
        pluses_and_minuses_new += old_str[i];
    }

    for (int i = length_min; i < pluses_and_minuses.length(); ++i) {
        pluses_and_minuses_new += pluses_and_minuses[i];
    }
    return pluses_and_minuses_new;
}

string picOfLines(const string &old_str, int index) {
    string pluses_and_minuses = "+";
    string line = "|";
    for (int i = 0; i < index; ++i) {
        int range;
        cin >> range;
        for (int j = 0; j < range; ++j) {
            pluses_and_minuses += "-";
            line += " ";
        }
        pluses_and_minuses += "+";
        line += "|";
    }

    string pluses_and_minuses_new = getSymbols(old_str, pluses_and_minuses);
    cout << pluses_and_minuses_new << "\n";
    cout << line << "\n";
    return pluses_and_minuses;
}

int main() {
    int n;
    cin >> n;
    string result;
    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        result = picOfLines(result, number);
    }
    cout << result;
    return 0;
}
