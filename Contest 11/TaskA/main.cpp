#include <iostream>
#include <utility>

using std::cin;
using std::cout;

struct Edge {
    int first, second, distance;

    explicit Edge(int first = 0, int second = 0, int distance = 0) {
        this->first = first;
        this->second = second;
        this->distance = distance;
    }

    ~Edge() = default;
};

class School {
    Edge *array_of_points_;
    int *array_;
    int *size_;
    int capacity_points_;
    int capacity_schools_;

public:
    School(int possible_lines, int schools) {
        this->capacity_points_ = possible_lines;
        this->capacity_schools_ = schools;
        this->array_of_points_ = new Edge[possible_lines]();
        this->array_ = new int[schools + 1];
        this->size_ = new int[schools + 1];
    }

    int partition(int low, int high) {
        int pivot = array_of_points_[high].distance;
        int index = (low - 1);
        for (int j = low; j <= high - 1; ++j) {
            if (array_of_points_[j].distance < pivot) {
                ++index;
                std::swap(array_of_points_[index], array_of_points_[j]);
            }
        }
        std::swap(array_of_points_[index + 1], array_of_points_[high]);
        return (index + 1);
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    void initialize() {
        for (int index = 1; index <= capacity_schools_; ++index) {
            array_[index] = index;
            size_[index] = 1;
        }
        for (int i = 0; i < capacity_points_; ++i) {
            int first, second, distance;
            cin >> first >> second >> distance;
            array_of_points_[i] = Edge(first, second, distance);
        }
        quickSort(0, capacity_points_ - 1);
    }

    ~School() {
        delete[] array_;
        delete[] size_;
        delete[] array_of_points_;
    }

    int recursiveFindId(int index) {
        if (index == array_[index]) {
            return index;
        }
        return array_[index] = recursiveFindId(array_[index]);
    }

    int unionSet(int first, int second) {
        first = recursiveFindId(first);
        second = recursiveFindId(second);
        if (first != second) {
            if (size_[first] < size_[second]) {
                std::swap(first, second);
            }
            array_[second] = first;
            if (size_[first] == size_[second]) {
                ++size_[first];
            }
            return 1;
        } else {
            return 0;
        }
    }

    int minPrice() {
        int mst_first_min = 0;
        for (int index = 0; index < capacity_points_; ++index) {
            if (!unionSet(array_of_points_[index].first, array_of_points_[index].second)) {
                continue;
            }
            mst_first_min += array_of_points_[index].distance;
        }
        return mst_first_min;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int schools, possible_lines;
    std::cin >> schools >> possible_lines;
    auto *school = new School(possible_lines, schools);
    school->initialize();
    std::cout << school->minPrice() << "\n";
    delete school;
    return 0;
}
