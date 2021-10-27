#include <iostream>
#include <string>

int main() {
    std::string input;
    getline(std::cin, input);
    std::string out_first, out_second;
    for (int i = 0; i < input.length(); ++i) {
        if (input[i] != '#') {
            (i % 2) == 0 ? (out_first.append(1, input[i])) : (out_second.append(1, input[i]));
        }
    }
    bool has_hashtag = false;
    std::string out_second_reversed;
    for (int i = out_second.length() - 1; i >= 0; i--) {
        if (out_second[i] != '#') {
            out_second_reversed.append(1, out_second[i]);
        } else {
            has_hashtag = true;
        }
    }

    std::string result = (out_first + out_second_reversed) + (!has_hashtag ? "#" : "");
    std::cout << result;
    return 0;
}
