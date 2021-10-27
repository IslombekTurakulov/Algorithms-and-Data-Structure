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

    void mergeSort(List *list);

    void removeFirst();

    void listSort();

    ~List();

    friend std::ostream &operator<<(std::ostream &out, const List &obj);
};

List::List() {
    head_node_ = nullptr;
    tail_node_ = nullptr;
    length_of_node_ = 0;
}

void List::listSort() {
    Node<int> *new_head = nullptr;
    while (head_node_ != nullptr) {
        Node<int> *node = head_node_;
        tail_node_ = head_node_;
        head_node_ = head_node_->getNext();
        if (new_head != nullptr && node->getData() >= new_head->getData()) {
            Node<int> *current = new_head;
            while (current->getNext() != nullptr &&
                   node->getData() >= current->getNext()->getData()) {
                current = current->getNext();
            }
            node->setNext(current->getNext());
            current->setNext(node);
        } else {
            node->setNext(new_head);
            new_head = node;
        }
    }
    head_node_ = new_head;
}

void List::mergeSort(List *list) {
    Node<int> *temp = list->head_node_;
    while (list->length_of_node_ != 0) {
        insert(temp->getData());
        list->removeFirst();
        temp = list->head_node_;
    }
    listSort();
}

void List::removeFirst() {
    if (head_node_ == nullptr) {
        return;
    }
    Node<int> *node_temp = head_node_->getNext();
    delete head_node_;
    head_node_ = node_temp;
    --length_of_node_;
    if (length_of_node_ != 0) {
        return;
    }
    head_node_ = nullptr;
    tail_node_ = nullptr;
}

void List::insert(int data) {
    if (head_node_ == nullptr) {
        head_node_ = new Node<int>(data);
        tail_node_ = head_node_;
        tail_node_->setNext(head_node_);
    } else {
        tail_node_->setNext(new Node<int>(data));
        tail_node_ = tail_node_->getNext();
    }
    ++length_of_node_;
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
    int first_length, second_length;
    cin >> first_length;
    cin >> second_length;
    List *first_list = new List();
    List *second_list = new List();

    createList(first_list, first_length);
    createList(second_list, second_length);

    first_list->mergeSort(second_list);
    cout << *first_list << "\n";

    delete first_list;
    delete second_list;
    return 0;
}
