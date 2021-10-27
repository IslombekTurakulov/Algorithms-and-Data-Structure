// Я дурачёк, 30 тестов делал на двусвязном списке)))
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

    void addElements(int num);

    void insert(int num, int position);

    void remove(int position);

    ~List();

    friend std::ostream &operator<<(std::ostream &out, const List &obj);

    void pushFront(int num);

    void pushBack(int num);
};

List::List() {
    head_node_ = nullptr;
    length_of_node_ = 0;
}

void List::pushBack(int num) {
    Node<int> *node = new Node<int>(num);
    ++length_of_node_;
    if (head_node_ != nullptr) {
        node = (tail_node_);
        tail_node_->setNext(node);
        tail_node_ = node;
    } else {
        head_node_ = node;
        tail_node_ = head_node_;
    }
}

void List::pushFront(int num) {
    Node<int> *new_node = new Node<int>(num);
    new_node->setNext(head_node_);
    head_node_ = new_node;
    if (tail_node_ == nullptr) {
        tail_node_ = head_node_;
    }
}

void List::remove(int position) {
    if (position == length_of_node_ - 1) {
        Node<int> *temp = head_node_;
        while (temp && temp->getNext()) {
            temp = temp->getNext();
        }
        head_node_ = temp;
        --length_of_node_;
        return;
    }
    if (position == -1) {
        Node<int> *temp = head_node_;
        head_node_ = head_node_->getNext();
        delete temp;
        --length_of_node_;
        return;
    }
    Node<int> *temp = head_node_, *prev, *next_temp;
    if (position == 0) {
        for (int i = 0; temp && i <= position; i++) {
            prev = temp;
            temp = temp->getNext();
        }
        next_temp = temp->getNext();
        delete temp;
        temp = next_temp;
        prev->setNext(temp);
        --length_of_node_;
        return;
    }
    ++position;
    for (int i = 0; temp != nullptr && i < position - 1; ++i) {
        temp = temp->getNext();
    }
    if (temp == nullptr || temp->getNext() == nullptr) {
        return;
    }
    Node<int> *next = temp->getNext()->getNext();
    delete temp->getNext();
    temp->setNext(next);
    --length_of_node_;
}

List::~List() {
    Node<int> *temp = nullptr;
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
    Node<int> *temp = head_node_;
    Node<int> *new_node = new Node<int>(num);
    for (int iteration = 0; iteration < position && temp->getNext(); ++iteration) {
        temp = temp->getNext();
    }
    new_node->setNext(temp->getNext());
    temp->setNext(new_node);
    ++length_of_node_;
}

void List::addElements(int num) {
    if (head_node_ == nullptr) {
        head_node_ = new Node<int>(num);
        tail_node_ = head_node_;
        tail_node_->setNext(head_node_);
    } else {
        tail_node_->setNext(new Node<int>(num));
        tail_node_ = tail_node_->getNext();
    }
    ++length_of_node_;
}

void createList(List *list, const int length) {
    for (int i = 0; i < length; ++i) {
        int temp;
        cin >> temp;
        list->addElements(temp);
    }
}

int main() {
    int first_length, second_length;
    cin >> first_length;
    cin >> second_length;
    List *first_list = new List();
    createList(first_list, first_length);
    for (int i = 0; i < second_length; ++i) {
        string input;
        cin >> input;
        if (input == "remove") {
            int position;
            cin >> position;
            first_list->remove(position);
        }
        if (input == "insert") {
            int value, position;
            cin >> value >> position;
            first_list->insert(value, position);
        }
    }
    cout << *first_list << "\n";
    delete first_list;
    return 0;
}
