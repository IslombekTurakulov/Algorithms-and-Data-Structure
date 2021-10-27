#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

void parseTheLine(string *time, string *hours, string *minutes, string *seconds) {
    int counter = 0;
    while (true) {
        string digit = (*time).substr((*time).find_last_of(':') + 1, time->length());
        if (counter == 0) {
            *seconds += digit;
        } else if (counter == 1) {
            *minutes += digit;
        } else if (counter == 2) {
            *hours += digit;
        }
        counter++;
        if (digit.size() != (*time).size()) {
            *time = (*time).erase((*time).length() - (digit.length() + 1));
        } else {
            break;
        }
    }
}

string getInt(int64_t hours) {
    string input = "";
    if (std::to_string(hours).length() == 1) {
        input = "0";
        input += std::to_string(hours);
    } else {
        input = std::to_string(hours);
    }
    return input;
}

int64_t parseTime(const std::string &input) {
    int64_t temp = 0;
    if (!input.empty()) {
        temp = std::stoi(input);
    }
    return temp;
}

int main() {
    string first_line, second_line;
    getline(cin, first_line);
    getline(cin, second_line);
    string first_hours, first_minutes, first_seconds;
    string second_hours, second_minutes, second_seconds;

    parseTheLine(&first_line, &first_hours, &first_minutes, &first_seconds);
    parseTheLine(&second_line, &second_hours, &second_minutes, &second_seconds);

    int64_t new_days = 0;
    int64_t new_hours = parseTime(first_hours) + parseTime(second_hours);
    int64_t new_minutes = parseTime(first_minutes) + parseTime(second_minutes);
    int64_t new_seconds = parseTime(first_seconds) + parseTime(second_seconds);

    new_minutes += new_seconds / 60;
    new_seconds %= 60;
    new_hours += new_minutes / 60;
    new_minutes %= 60;
    new_days = new_hours / 24;
    new_hours %= 24;

    if (new_days > 0) {
        cout << getInt(new_hours) << ":" << getInt(new_minutes)
             << ":" << getInt(new_seconds) << "+" << new_days
             << " days";
    } else {
        cout << getInt(new_hours) << ":" << getInt(new_minutes)
             << ":" << getInt(new_seconds);
    }
    return 0;
}
