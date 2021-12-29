#include <iostream>
#include <set>
#include <iomanip>

using std::cin;
using std::cout;

int main() {
    std::multiset<size_t> numbers;
    size_t size;
    cin >> size;
    for (size_t i = 0; i < size; ++i) {
        size_t number;
        cin >> number;
        numbers.insert(number);
    }
    double cost = 0;
    while (numbers.size() > 1) {
        auto first = numbers.begin();
        auto second = next(first);
        auto third = next(second);
        size_t result = *first + *second;
        numbers.erase(first, third);
        cost += result * 0.05;
        numbers.insert(result);
    }
    cout << std::setprecision(2) << std::fixed << cost;
    return 0;
}
