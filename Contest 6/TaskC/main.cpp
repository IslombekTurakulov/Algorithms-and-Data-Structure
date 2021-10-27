#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

template<typename T>
class Node {
private:
    Node<T> *next_node_, *prev_node_;
    int value_of_node_;

public:
    explicit Node(int value) {
        next_node_ = nullptr;
        prev_node_ = nullptr;
        value_of_node_ = value;
    }

    [[nodiscard]] int getData() const {
        return value_of_node_;
    }

    void setData(T num) {
        value_of_node_ = num;
    }

    void setNext(Node<T> *node) {
        next_node_ = node;
    }

    void setPrev(Node<T> *node) {
        prev_node_ = node;
    }

    Node<T> *getNext() {
        return next_node_;
    }

    Node<T> *getPrev() {
        return prev_node_;
    }
};

class List {
private:
    Node<int> *head_node_;
    Node<int> *tail_node_;
    int length_of_node_;

public:
    List();

    void pushBack(int num);

    void reverse();

    void pushFront(int num);

    void insert(int num, int position);

    void remove(int position);

    ~List();

    friend std::ostream &operator<<(std::ostream &out, const List &obj);
};

void showChance(int second_length, List *first_list);

List::List() {
    head_node_ = nullptr;
    length_of_node_ = 0;
}

void List::reverse() {
    for (int i = 0; tail_node_ && i < length_of_node_; ++i) {
        int value = tail_node_->getData();
        cout << value << " ";
        tail_node_ = tail_node_->getPrev();
    }
    cout << "\n";
    delete tail_node_;
    tail_node_ = nullptr;
}

void List::pushBack(int num) {
    Node<int> *new_node = new Node<int>(num);
    new_node->setNext(nullptr);
    if (length_of_node_ != 0) {
        tail_node_->setNext(new_node);
        new_node->setPrev(tail_node_);
        tail_node_ = new_node;
    } else {
        head_node_ = new_node;
        tail_node_ = new_node;
    }
    ++length_of_node_;
}

void List::pushFront(int num) {
    Node<int> *new_node = new Node<int>(num);
    new_node->setNext(nullptr);
    new_node->setPrev(nullptr);
    if (length_of_node_ != 0) {
        new_node->setNext(head_node_);
        head_node_->setPrev(new_node);
        head_node_ = new_node;
    } else {
        head_node_ = new_node;
        tail_node_ = new_node;
    }
    ++length_of_node_;
}

void List::remove(int position) {
    Node<int> *temp = head_node_;
    for (int i = 0; i <= position; ++i) {
        temp = temp->getNext();
    }
    if (temp->getPrev() == nullptr) {
        Node<int> *front = head_node_->getNext();
        if (front->getNext() != nullptr) {
            front->setPrev(nullptr);
        }
        delete head_node_;
        head_node_ = front;
    } else if (temp->getNext() == nullptr) {
        Node<int> *back = tail_node_->getPrev();
        if (back != nullptr) {
            back->setNext(nullptr);
        }
        tail_node_->setPrev(nullptr);
        delete tail_node_;
        tail_node_ = back;
    } else {
        Node<int> *next = temp->getNext();
        Node<int> *prev = temp->getPrev();
        next->setPrev(prev);
        prev->setNext(next);
        temp->setNext(nullptr);
        temp->setPrev(nullptr);
        delete temp;
        temp = nullptr;
    }
    --length_of_node_;
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

void List::insert(int num, int position) {
    if (position == length_of_node_ - 1) {
        pushBack(num);
        return;
    }
    if (position == -1) {
        pushFront(num);
        return;
    }
    Node<int> *new_node = new Node<int>(num), *temp = head_node_;
    for (int i = 0; temp && i < position; ++i) {
        temp = temp->getNext();
    }
    new_node->setNext(temp->getNext());
    new_node->setPrev(temp);
    temp->getNext()->setPrev(new_node);
    temp->setNext(new_node);

    ++length_of_node_;
}

void createList(List *list, const int length) {
    for (int i = 0; i < length; ++i) {
        int temp;
        cin >> temp;
        list->pushBack(temp);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int first_length, second_length;
    cin >> first_length;
    cin >> second_length;
    List *first_list = new List();
    createList(first_list, first_length);
    showChance(second_length, first_list);
    cout << *first_list << "\n";
    first_list->reverse();
    delete first_list;
    return 0;
}

void showChance(int second_length, List *first_list) {
    string input;
    for (int i = 0; i < second_length; ++i) {
        cin >> input;
        if (input == "push_back") {
            int num = 0;
            cin >> num;
            first_list->pushBack(num);
        }
        if (input == "push_front") {
            int num = 0;
            cin >> num;
            first_list->pushFront(num);
        }
        if (input == "remove") {
            int position = 0;
            cin >> position;
            first_list->remove(position);
        }
        if (input == "insert") {
            int value = 0, position = 0;
            cin >> value >> position;
            first_list->insert(value, position);
        }
    }
}
