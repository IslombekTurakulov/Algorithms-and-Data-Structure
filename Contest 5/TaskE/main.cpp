#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::string_view;
using std::to_string;

string recursiveUnpackingLikeAmazon(string input);

int main() {
    string input;
    getline(cin, input);
    // Результат вызова рекурсивной функции
    cout << recursiveUnpackingLikeAmazon(input) << "\n";
    return 0;
}

// Хотел сделать через ссылку, но из-за рекурсии не придумал ничего кроме этого.
string recursiveUnpackingLikeAmazon(string input) {
    string unpacked_result;
    string word = "";
    int iterations = 0;
    size_t length_of_input = input.length();
    while (iterations < length_of_input) {
        word = "";
        // проверяем на цифры, если это буква, то плюсуем в unpacked_result
        if (input[iterations] < '0' || input[iterations] > '9') {
            unpacked_result += input[iterations];
        } else {
            // если это число, то через парсинг инициализируем в num_to_multiply
            auto num_to_multiply = std::stoi(to_string(input[iterations] - '0'));
            iterations += 2;
            auto has_brace = 1;
            // тут идёт проверка на существование буквы.
            while (true) {
                if (input[iterations] != '[') {
                    if (input[iterations] == ']') {
                        --has_brace;
                    }
                } else {
                    ++has_brace;
                }
                if (has_brace != 0) {
                    word += input[iterations];
                    ++iterations;
                } else {
                    break;
                }
            }
            // Выполняется рекурсия, т.е. повторяются те же моменты, что и в прошлый рах
            // Например 1[a1[b]]
            // Мы изначально прочитали 1[a... затем мы идём рекурсивно,
            // чтобы прочитать дальше, т.е. 1[b]
            string recursive_unpacked = recursiveUnpackingLikeAmazon(word);
            for (auto i = 0; i < num_to_multiply; ++i) {
                unpacked_result += recursive_unpacked;
            }
        }
        ++iterations;
    }
    // cout << unpacked_result << "\n";
    return unpacked_result;
}
