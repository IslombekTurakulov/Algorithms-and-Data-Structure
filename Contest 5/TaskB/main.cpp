/* HSE Contest 5, Turakulov Islombek 3.10.2021
 * push_front n: Добавить в голову дека новый элемент n (задается через пробел).
 * Программа должна вывести ok.
 * push_back n: Добавить в хвост дека новый элемент n (задается через пробел).
 * Программа должна вывести ok.
 * pop_front: Извлечь элемент из головы дека. Программа должна вывести его значение.
 * pop_back: Извлечь элемент из хвоста дека. Программа должна вывести его значение.
 * front: Узнать значение головного элемента (не удаляя его). Программа должна вывести его значение.
 * back: Узнать значение хвостового элемента (не удаляя его). Программа должна вывести его значение.
 * size: Вывести количество элементов в деке.
 * clear: Очистить дек (удалить из него все элементы) и вывести ok.
 * exit: Программа должна вывести bye и завершить работу.
 */

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::to_string;

struct Node {
    int value;
    Node *next, *prev;
};

class deque {
    Node *top;
    Node *tail;
    int count;

 public:
    deque();

    void push_back(int num);

    void push_front(int num);

    void pop_back();

    void pop_front();

    void back();

    void front();

    void size() const;

    void clear();

    static void exit();
};

deque::deque() {
    top = nullptr;
    tail = nullptr;
    count = 0;
}

void deque::push_back(int num) {
    // выделение памяти под новый элемент структуры
    Node *node = new Node;
    node->value = num;
    count++;
    if (top != nullptr) {
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        top = node;
        tail = top;
    }
    cout << "ok" << "\n";
}

void deque::push_front(int num) {
    Node *node = new Node;
    node->value = num;
    count++;
    if (top != nullptr) {
        node->next = top;
        top->prev = node;
        top = node;
    } else {
        top = node;
        tail = top;
    }
    cout << "ok" << "\n";
}

void deque::pop_back() {
    //если дек не пустой
    if (count != 0) {
        cout << tail->value << "\n";
        if (count <= 1) {
            top = nullptr;
            tail = nullptr;
            count--;
        } else {
            Node *node = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete node;
            count--;
        }
    } else {
        cout << "error" << "\n";
    }
}

void deque::pop_front() {
    if (count != 0) {
        cout << top->value << "\n";
        if (!top->next) {
            if (top == tail) {
                top->next = nullptr;
                top = nullptr;
                delete top;
                count = 0;
            }
        } else {
            Node *node = top;
            top = top->next;
            top->prev = nullptr;
            delete node;
            count--;
        }
    } else {
        cout << "error" << "\n";
    }
}

void deque::back() {
    cout << (count != 0 ? to_string(tail->value) : "error") << "\n";
}

void deque::front() {
    cout << (count != 0 ? to_string(top->value) : "error") << "\n";
}

void deque::size() const {
    cout << count << "\n";
}

void deque::clear() {
    count = 0;
    cout << "ok" << "\n";
    while (top) {
        tail = top->next;
        delete top;
        top = tail;
    }
}

void deque::exit() {
    cout << "bye" << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    deque deque;
    string input;
    while (cin >> input && input != "exit") {
        if (input == "push_front") {
            int number;
            cin >> number;
            deque.push_front(number);
        }
        if (input == "push_back") {
            int number;
            cin >> number;
            deque.push_back(number);
        }
        if (input == "pop_front") {
            deque.pop_front();
        }
        if (input == "pop_back") {
            deque.pop_back();
        }
        if (input == "clear") {
            deque.clear();
        }
        if (input == "size") {
            deque.size();
        }
        if (input == "front") {
            deque.front();
        }
        if (input == "back") {
            deque.back();
        }
        if (input == "exit") {
            deque::exit();
            break;
        }
    }
    if (input == "exit") {
        deque::exit();
    }
    return 0;
}
