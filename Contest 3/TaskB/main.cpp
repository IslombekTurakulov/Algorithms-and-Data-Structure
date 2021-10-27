#include <iostream>
#include <vector>
#include <algorithm>

int countMinOperations(std::vector<int> *vector_of_numbers, const int &n) {
    int answer = 0;
    while (true) {
        // Подсчитываем количество нулей
        int zero_counter = 0;
        // Цикл for нужен для нахождения нечётных чисел для дальнейших операций
        int iteration;
        bool is_even = false;
        for (iteration = 0; iteration < n; iteration++) {
            if ((*vector_of_numbers)[iteration] == 0) {
                zero_counter++;
            } else if ((*vector_of_numbers)[iteration] % 2 != 0) {
                (*vector_of_numbers)[iteration] += (*vector_of_numbers)[iteration] > 0 ? -1 : 1;
                answer++;
                is_even = true;
            }
        }
        if (zero_counter == n) {
            break;
        }
        // Если все элементы чётные
        if (!is_even) {
            for (auto &number : (*vector_of_numbers)) {
                number /= 2;
            }
            answer++;
        }
    }
    return answer;
}

int main() {
    // https://codeforces.com/blog/entry/5217?locale=ru
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> vector_of_numbers(n, 0);
    for (int &number : vector_of_numbers) {
        std::cin >> number;
    }
    std::cout << countMinOperations(&vector_of_numbers, n);
    return 0;
}
