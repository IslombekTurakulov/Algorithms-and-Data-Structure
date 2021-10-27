#include <iostream>
#include <string>

bool compare(std::string first_input, std::string second_input) {
    return first_input == second_input;
}

int main() {
    std::string first_input, second_input;
    std::cin >> first_input >> second_input;
    if (compare(first_input, second_input)) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }
    return 0;
}