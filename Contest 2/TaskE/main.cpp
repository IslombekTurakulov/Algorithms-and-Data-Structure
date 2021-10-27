#include <iostream>

void fibonacci(std::string &first, std::string &second, std::string &temp, int m);

int main() {
    std::string first;
    std::string second;
    std::cin >> first;
    std::cin >> second;
    std::string temp = second;
    second = first + second;
    first = temp;
    int n;
    int m;
    std::cin >> n;
    std::cin >> m;
    fibonacci(first, second, temp, m);

}

void fibonacci(std::string &first, std::string &second, std::string &temp, int m) {
    while (second.length() <= m){
        temp = second;
        second = first + second;
        first = temp;
    }

    std::cout << second[m - 1];
}
