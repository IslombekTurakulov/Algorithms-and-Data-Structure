#include <iostream>
#include <cmath>
#include <vector>

// Не смог сделать декомпозицию, не душите пожалуйста :(
int main() {
    // https://codeforces.com/blog/entry/5217?locale=ru
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // Создаём два вектора для подсчёта цифр и количества.
    std::vector<int> secondLineVector(100000);
    std::vector<int> secondLineCounter(100000);
    // Объявляем переменные.
    int firstIndex, secondIndex = -1;
    int elementOfK, thirdLineInput, firstLineInputN;
    int L, R, result, tempL, tempR;
    std::cin >> firstLineInputN;
    elementOfK = sqrt(firstLineInputN);
    // Ввод второй строки.
    for (firstIndex = 0; firstIndex < firstLineInputN; ++firstIndex) {
        std::cin >> secondLineVector[firstIndex];
        if (firstIndex % elementOfK == 0) {
            secondIndex++;
            secondLineCounter[secondIndex] = 0;
        }
        if (secondLineVector[firstIndex] == 0) {
            secondLineCounter[secondIndex]++;
        }
    }
    // Ввод третьей строки.
    std::cin >> thirdLineInput;
    while (thirdLineInput) {
        thirdLineInput--;
        result = 0;
        // Ввод двух чисел
        std::cin >> L >> R;
        tempL = --L / elementOfK;
        tempR = --R / elementOfK;
        if (tempL != tempR) {
            for (firstIndex = L; firstIndex < (tempL + 1) * elementOfK; ++firstIndex) {
                if (secondLineVector[firstIndex] == 0) {
                    result++;
                }
            }
            for (secondIndex = tempL + 1; secondIndex < tempR; ++secondIndex) {
                result += secondLineCounter[secondIndex];
            }
            for (firstIndex = tempR * elementOfK; firstIndex <= R; ++firstIndex) {
                if (secondLineVector[firstIndex] == 0) {
                    result++;
                }
            }
        } else {
            for (firstIndex = L; firstIndex <= R; ++firstIndex) {
                if (secondLineVector[firstIndex] == 0) {
                    result++;
                }
            }
        }
        // Вывод результата.
        std::cout << result << " ";
    }
    return 0;
}
