// Какой алгоритм был взят: https://e-maxx.ru/algo/dsu
#include <iostream>
#include <utility>
#include <algorithm>

class DSU {
    int *parent_;
    int *size_;

public:
    explicit DSU(int capacity) {
        parent_ = new int[capacity];
        size_ = new int[capacity];
    }

    void init(int capacity) {
        for (int x = 0; x < capacity; ++x) {
            parent_[x] = x;
            size_[x] = 1;
        }
    }

    ~DSU() {
        delete[] parent_;
        delete[] size_;
    }

    int findSet(int id) {
        if (parent_[id] == id) {
            return id;
        }
        return parent_[id] = findSet(parent_[id]);
    }

    int unionSet(int id, int bridges) {
        id = findSet(id);
        bridges = findSet(bridges);
        if (id != bridges) {
            if (size_[id] < size_[bridges]) {
                std::swap(id, bridges);
            }
            parent_[bridges] = id;
            size_[id] += size_[bridges];
        }
        return size_[id];
    }
};

int main() {
    int amount_of_islands, amount_of_bridges, first, second;
    std::cin >> amount_of_islands >> amount_of_bridges;
    DSU *dsu = new DSU(amount_of_islands + 1);
    dsu->init(amount_of_islands + 1);
    int index;
    for (index = 1; index <= amount_of_bridges; ++index) {
        std::cin >> first >> second;
        if (dsu->unionSet(first, second) == amount_of_islands) {
            break;
        }
    }
    std::cout << index;
    delete dsu;
    return 0;
}
