#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::ostringstream;

void getIteration(string *first_iteration_string);

int main() {
    // Решил попробовать новые функции с семинара 4
    int first_iteration, x;
    cin >> first_iteration >> x;
    string first_iteration_string = std::to_string(first_iteration);
    while (--x) {
        getIteration(&first_iteration_string);
    }
    cout << first_iteration_string << "\n";
    return 0;
}

void getIteration(string *first_iteration_string) {
    ostringstream string_stream(std::ios_base::app);
    size_t count = 1;
    auto current_iterator = std::next((*first_iteration_string).begin());
    auto previous_iterator = (*first_iteration_string).begin();
    for (; current_iterator != (*first_iteration_string).end(); ++current_iterator) {
        if (*current_iterator == *previous_iterator) {
            ++count;
        } else {
            string_stream << count << (*previous_iterator);
            count = 1;
            previous_iterator = current_iterator;
        }
    }
    string_stream << count << (*previous_iterator);
    (*first_iteration_string) = string_stream.str();
}
