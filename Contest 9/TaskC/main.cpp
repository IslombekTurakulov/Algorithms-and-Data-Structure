#include <iostream>

using std::cin;
using std::cout;

class DSU {
    int *child_;
    int *root_;
    int *parent_;
    int capacity_;

public:
    explicit DSU(int size) {
        child_ = new int[size];
        root_ = new int[size];
        parent_ = new int[size];
        for (int i = 0; i < size; ++i) {
            child_[i] = i;
            parent_[i] = i;
            root_[i] = i;
        }
        capacity_ = size;
    }

    ~DSU() {
        delete[] child_;
        delete[] parent_;
        delete[] root_;
    }

    void addToEdges(int first, int second) {
        int child_id = findMinT(first);
        int root_id = findMinTail(second);
        if (child_id != root_id) {
            child_[child_id] = root_id;
            root_[root_id] = findMinTail(first);
            parent_[child_id] = findMinT(second);
        }
    }

    int findMinTail(int id) {
        return root_[id] == id ? id : (root_[id] = findMinTail(root_[id]));
    }

    int findMinT(int id) {
        return parent_[id] == id ? id : (parent_[id] = findMinT(parent_[id]));
    }

    void print() {
        int pos = findMinTail(1);
        while (child_[pos] != pos) {
            cout << pos << " ";
            pos = child_[pos];
        }
        cout << pos << "\n";
    }
};

int main() {
    int size;
    cin >> size;
    DSU *dsu = new DSU(size + 1);
    for (int i = 1; i < size; ++i) {
        int first, second;
        cin >> first >> second;
        dsu->addToEdges(first, second);
    }
    dsu->print();
    delete dsu;
    return 0;
}
