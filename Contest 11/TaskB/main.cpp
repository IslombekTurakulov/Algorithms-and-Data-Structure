#include <iostream>
#include <utility>
#include <algorithm>

using std::cin;
using std::cout;

struct Edge {
    int first, second, cost;

    explicit Edge(int first = 0, int second = 0, int cost = 0) {
        this->first = first;
        this->second = second;
        this->cost = cost;
    }

    ~Edge() = default;
};

class DSU {
    int *array_;
    int *size_;
    int *school_edges_;
    Edge *school_;
    int capacity_lines_;
    int capacity_schools_;

    int partition(int low, int high) {
        int pivot = school_[high].cost;
        int index = (low - 1);
        for (int j = low; j <= high - 1; ++j) {
            if (school_[j].cost < pivot) {
                ++index;
                std::swap(school_[index], school_[j]);
            }
        }
        std::swap(school_[index + 1], school_[high]);
        return (index + 1);
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

public:
    DSU(int schools, int school_lines) {
        array_ = new int[schools];
        size_ = new int[schools];
        school_edges_ = new int[school_lines];
        school_ = new Edge[school_lines];
        capacity_lines_ = school_lines;
        capacity_schools_ = schools;
    }

    ~DSU() {
        delete[] array_;
        delete[] size_;
        delete[] school_edges_;
        delete[] school_;
    }

    void initialize() {
        for (int index = 1; index <= capacity_schools_; ++index) {
            array_[index] = index;
            size_[index] = 1;
        }
        for (int index = 0; index < capacity_lines_; ++index) {
            int first, second, price;
            cin >> first >> second >> price;
            school_[index] = Edge(first, second, price);
        }
        quickSort(0, capacity_lines_ - 1);
    }

    void calculate() {
        int mst_first_min = 0;
        int temp_capacity = 0;
        for (int index = 0; index < capacity_schools_; ++index) {
            if (unionSet(school_[index].first, school_[index].second)) {
                mst_first_min += school_[index].cost;
                school_edges_[index] = index;
                ++temp_capacity;
            }
        }
        int mst_second_min = 1000001;
        for (int iteration = 0; iteration < temp_capacity; ++iteration) {
            int len = 0;
            int cnt = 1;
            for (int index = 1; index <= capacity_schools_; ++index) {
                array_[index] = index, size_[index] = 1;
            }
            for (int index = 0; index < capacity_lines_; ++index) {
                if (index == school_edges_[iteration]) {
                    continue;
                }
                if (unionSet(school_[index].first, school_[index].second)) {
                    len += school_[index].cost;
                    ++cnt;
                }
            }
            if (cnt == capacity_lines_) {
                if (len < mst_second_min) {
                    mst_second_min = len;
                }
            }
        }
        cout << mst_first_min << " " << mst_second_min << "\n";
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
        if (first == second) {
            return 0;
        }
        if (size_[first] < size_[second]) {
            std::swap(first, second);
        }
        array_[second] = first;
        if (size_[first] == size_[second]) {
            ++size_[first];
        }
        return 1;
    }
};

int main() {
    int schools, school_lines;
    cin >> schools >> school_lines;
    DSU *dsu = new DSU(schools, school_lines);
    dsu->initialize();
    dsu->calculate();
    delete dsu;
    return 0;
}
