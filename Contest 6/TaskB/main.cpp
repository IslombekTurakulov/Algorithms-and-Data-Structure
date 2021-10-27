#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

template <typename T>
class Node {
private:
    Node<T> *next_node_;
    int value_of_node_;

public:
    explicit Node(int value) {
        next_node_ = nullptr;
        value_of_node_ = value;
    }

    [[nodiscard]] int getData() const {
        return value_of_node_;
    }

    void setNext(Node<T> *node) {
        next_node_ = node;
    }

    Node<T> *getNext() {
        return next_node_;
    }
};

class List {
private:
    Node<int> *head_node_;
    Node<int> *tail_node_;
    int length_of_node_;

public:
    List();

    void insert(int data);

    ~List();

    friend std::ostream &operator<<(std::ostream &out, const List &obj);
    void reverse();
};

List::List() {
    head_node_ = nullptr;
    tail_node_ = nullptr;
    length_of_node_ = 0;
}

void List::insert(int data) {
    Node<int> *new_node = new Node<int>(data);
    new_node->setNext(tail_node_);
    tail_node_ = new_node;
    ++length_of_node_;
}

void List::reverse() {
    head_node_ = tail_node_;
}

List::~List() {
    Node<int> *temp;
    while (head_node_ != nullptr) {
        temp = head_node_->getNext();
        delete head_node_;
        head_node_ = temp;
    }
}

std::ostream &operator<<(std::ostream &out_stream, const List &obj) {
    auto *current = obj.head_node_;
    while (current != nullptr) {
        int value = current->getData();
        out_stream << value << " ";
        current = current->getNext();
    }
    return out_stream;
}

void createList(List *list, const int length) {
    for (int i = 0; i < length; ++i) {
        int temp;
        cin >> temp;
        list->insert(temp);
    }
}

int main() {
    int length;
    cin >> length;
    List *first = new List();
    createList(first, length);
    first->reverse();
    cout << *first << "\n";
    delete first;
    return 0;
}
