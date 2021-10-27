#include <iostream>

void rec(int times) {
    if (times <= 0) {
        return;
    }
    int input_number;
    std::cin >> input_number;
    rec(times - 1);
    std::cout << input_number << " ";
}

int main() {
    int input;
    std::cin >> input;
    rec(input);
}