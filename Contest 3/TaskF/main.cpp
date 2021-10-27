#include <iostream>

int main() {
    int64_t n, m;
    std::cin >> n;
    std::cin >> m;
    auto **array = new int64_t *[n];
    for (int64_t i = 0; i < n; i++) {
        array[i] = new int64_t[m];
        for (int64_t j = 0; j < m; j++) {
            array[i][j] = i == 0 || j == 0 ? 1 : array[i - 1][j] + array[i][j - 1];
            std::cout << array[i][j] << " ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    return 0;
}
