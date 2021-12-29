#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    std::map<string, int> dict;
    int commands, attempts;
    cin >> commands >> attempts;
    vector<int> result(commands, 0);
    int iteration = 0;
    while (iteration < attempts) {
        int input;
        string clothes;
        cin >> input >> clothes;
        dict[clothes] = input;
        ++iteration;
    }
    for (auto& item : dict) {
        if (item.second < 0) {
            continue;
        }
        ++result[item.second - 1];
    }
    iteration = 0;
    while (iteration < commands) {
        cout << result[iteration] << " ";
        ++iteration;
    }
    return 0;
}
