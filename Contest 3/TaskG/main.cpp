#include <iostream>

void **rotateMatrix(int **source_matrix, int **rotated_array, int n, int m) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated_array[i][j] = source_matrix[n - j - 1][i];
        }
    }
}

void output(int n, int m, int *const *coup) {
    std::cout << m << " " << n << "\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << coup[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int m;
    int n;
    std::cin >> n;
    std::cin >> m;
    // Filling array to the new arrays.
    int **source_of_matrix = new int *[n];
    int **rotated_array = new int *[m];
    for (int j = 0; j < m; j++) {
        rotated_array[j] = new int[n];
    }
    for (int j = 0; j < n; j++) {
        source_of_matrix[j] = new int[m];
    }
    // Filling array with numbers.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> source_of_matrix[i][j];
        }
    }
    // Rotate the matrix to 90.
    rotateMatrix(source_of_matrix, rotated_array, n, m);
    output(n, m, rotated_array);
    // Deleting arrays.
    for (int i = 0; i < n; i++) {
        delete[] source_of_matrix[i];
    }
    for (int i = 0; i < m; ++i) {
        delete[] rotated_array[i];
    }
    delete[] source_of_matrix;
    delete[] rotated_array;
    source_of_matrix = nullptr;
    rotated_array = nullptr;
    return 0;
}
