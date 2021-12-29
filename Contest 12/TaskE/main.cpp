#include <iostream>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;

int main() {
    int64_t length;
    cin >> length;
    char previous_symbol = '+';
    int64_t result_of_previous = 0;
    std::set<int64_t> vector;
    int64_t max_mod = 1000000000;
    for (int index = 0; index < length; ++index) {
        char current_symbol;
        cin >> current_symbol;
        if (current_symbol == '+') {
            int64_t number;
            cin >> number;
            if (previous_symbol == '?') {
                vector.insert((number + result_of_previous) % max_mod);
            } else {
                vector.insert(number);
            }
        } else {
            int64_t number;
            cin >> number;
            auto next = vector.lower_bound(number);
            if (next != vector.end()) {
                cout << (result_of_previous = *next) << "\n";
            } else {
                cout << (result_of_previous = -1) << "\n";
            }
        }
        previous_symbol = current_symbol;
    }
    return 0;
}
