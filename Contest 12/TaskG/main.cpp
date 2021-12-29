#include <iostream>
#include <set>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;
using std::string;

int64_t findMax(const std::set<int64_t> &my_set) {
    int64_t max_element = 0;
    if (!my_set.empty()) {
        max_element = *(my_set.rbegin());
    }
    return max_element;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t size;
    cin >> size;
    std::set<int64_t> array;
    std::set<int64_t> counter;
    for (uint64_t i = 0; i < size; ++i) {
        int64_t number;
        cin >> number;
        array.insert(number);
    }
    int64_t count = 1;
    counter.insert(count);
    auto first = array.begin();
    bool flag = true;
    for (int64_t index = 1; index < size; ++index) {
        auto next_num = next(first);
        int64_t number = *next_num - *first;
        if (number == 1) {
            ++count;
        } else {
            counter.insert(count);
            count = 1;
            flag = false;
        }
        first = next_num;
    }
    if (flag) {
        cout << count << "\n";
    } else {
        cout << findMax(counter) << "\n";
    }
    return 0;
}
