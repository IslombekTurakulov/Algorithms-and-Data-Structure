#include <iostream>
#include <vector>
#include <stack>

void initialize(size_t length, int64_t *cost_of_living);

using std::cin;
using std::cout;
using std::stack;
using std::vector;

int main() {
    stack<int64_t> city_id;
    stack<int64_t> city_id_cost;
    size_t length;
    cin >> length;
    // Вектор размера length состоит из -1 цифр.
    vector<int> result(length, -1);
    auto *cost_of_living = new int64_t[length];
    initialize(length, cost_of_living);
    city_id.push(-1);
    city_id_cost.push(-1);
    int index = 0;
    while (index < length) {
        int64_t cost = cost_of_living[index];
        while (city_id_cost.top() > cost) {
            result[city_id.top()] = index;
            city_id_cost.pop();
            city_id.pop();
        }
        city_id_cost.push(cost);
        city_id.push(index);
        ++index;
    }
    index = 0;
    while (index < length) {
        cout << result[index] << " ";
        ++index;
    }
    delete[] cost_of_living;
    return 0;
}

void initialize(size_t length, int64_t *cost_of_living) {
    for (int64_t i = 0; i < length; ++i) {
        cin >> cost_of_living[i];
    }
}
