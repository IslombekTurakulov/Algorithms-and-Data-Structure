#include <iostream>
#include <vector>

std::vector<int> shiftArray(const std::vector<int> &array, int shift) {
    std::vector<int> shifted_array(array.size(), 0);
    // Сдвиги вправо.
    for (int i = 0; i < array.size(); ++i) {
        shifted_array[(i + shift) % array.size()] = array[i];
    }
    return shifted_array;
}

bool checkForUnique(const std::vector<std::vector<int>> &array_of_arrays,
                    const std::vector<int> &array) {
    bool unique_or_not = false;
    // Позволяет брать только уникальный объект.
    for (const auto &array_item : array_of_arrays) {
        for (int j = 0; j < array_item.size(); ++j) {
            if (array_item[j] == array[j]) {
                continue;
            }
            unique_or_not = true;
            break;
        }
        if (!unique_or_not) {
            return false;
        }
    }

    return true;
}

int16_t hammingDistance(const std::vector<int> &first_array, const std::vector<int> &second_array) {
    int16_t count_difference = 0;
    // Расчёт расстояния.
    for (int i = 0; i < first_array.size(); ++i) {
        if (first_array[i] != second_array[i]) {
            count_difference += 1;
        }
    }
    return count_difference;
}


int main() {
    std::vector<std::vector<int>> rotated_arrays;
    int16_t hamming_max_distance = INT16_MIN;
    std::vector<int16_t> collection_of_shifts;
    std::vector<int16_t> iteration_distances;
    int16_t n;
    std::cin >> n;
    std::vector<int> numbers(n, 0);
    for (int &number : numbers) {
        std::cin >> number;
    }
    // Пробегаемся циклом.
    for (int16_t shift = 0; shift < n; ++shift) {
        std::vector<int> temp_array = shiftArray(numbers, shift);
        int16_t distance = hammingDistance(numbers, temp_array);
        if (checkForUnique(rotated_arrays, temp_array)) {
            rotated_arrays.push_back(temp_array);
            collection_of_shifts.push_back(shift);
            iteration_distances.push_back(distance);
        }
        if (distance > hamming_max_distance) {
            hamming_max_distance = distance;
        }
    }
    if (n != 0) {
        std::cout << hamming_max_distance << "\n";
    }

    for (int i = 0; i < rotated_arrays.size(); ++i) {
        if (iteration_distances[i] == hamming_max_distance) {
            for (int16_t j = 0; j < n; ++j) {
                if (j + 1 == n) {
                    std::cout << std::to_string(rotated_arrays[i][j]) << "; "
                    + std::to_string(collection_of_shifts[i]) + "\n";
                } else {
                    std::cout << std::to_string(rotated_arrays[i][j]) << " ";
                }
            }
        }
    }
    return 0;
}
