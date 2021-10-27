#include <iostream>
#include <string>

using std::string;
using std::cin;

int getInt(const string &first_input, int first_input_spaces, int index) {
    for (index = 0; first_input[index]; index++) {
        if (first_input[index] == ' ') {
            first_input_spaces++;
        }
    }
    return first_input_spaces;
}

int main() {
    string first_input, second_input;
    getline(cin, first_input);
    getline(cin, second_input);
    int first_input_spaces = 0, second_input_spaces = 1, index;
    first_input_spaces = getInt(first_input, first_input_spaces, index);
    second_input_spaces = getInt(second_input, second_input_spaces, index);
    first_input_spaces %= second_input_spaces;
    for (index = 0; first_input_spaces > 0; index++) {
        if (second_input[index] == ' ') {
            first_input_spaces--;
        }
    }
    while (second_input[index] && second_input[index] != ' ') {
        putchar(second_input[index++]);
    }
    return 0;
}
