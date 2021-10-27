#include <iostream>

int reverse(int n) {
    int temp_num, result = 0;
    while (n > 0) {
        temp_num = n % 10;
        result = result * 10 + temp_num;
        n /= 10;
    }
    return result;
}

int main() {

    int input, count_palindromes = 0;
    std::cin >> input;
    for (int i = 1; i <= input; i++) {
        if (i == reverse(i)) {
            count_palindromes++;
        }
    }
    std::cout << count_palindromes;
}