#include <iostream>
#include <algorithm>
#include <vector>

// https://e-maxx.ru/algo/segment_tree Дерево отрезков.
void build(const std::vector<int> &array, std::vector<int> *tree,
           int index, int left_tree, int right_tree) {
    if (left_tree == right_tree) {
        (*tree)[index] = array[left_tree];
    } else {
        int len = (left_tree + right_tree) / 2;
        build(array, tree, index * 2, left_tree, len);
        build(array, tree, index * 2 + 1, len + 1, right_tree);
        (*tree)[index] = std::min((*tree)[index * 2], (*tree)[index * 2 + 1]);
    }
}

int get_min(const std::vector<int> &tree, int index, int left,
            int right, int i, int k) {
    if (i > k) {
        return INT16_MAX;
    }
    if (i == left && k == right) {
        return tree[index];
    }
    int len = (left + right) / 2;
    return std::min(get_min(tree, index * 2, left, len, i, std::min(k, len)),
                    get_min(tree, index * 2 + 1, len + 1,
                            right, std::max(i, len + 1), k));
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> vector_of_tree(4 * n, 0);
    std::vector<int> vector_numbers;
    // Инициализация ввода.
    for (int i = 0; i < n; ++i) {
        int input;
        std::cin >> input;
        (vector_numbers).push_back(input);
    }
    // Строим дерево отрезков.
    build(vector_numbers, &vector_of_tree, 1, 0, n - 1);
    // Пробегаемся через цикл и выводим минимальные числа.
    for (int i = 0; i <= n - k; ++i) {
        int temp = get_min(vector_of_tree, 1, 0, n - 1, i, i + k - 1);
        std::cout << temp << " ";
    }
    return 0;
}
