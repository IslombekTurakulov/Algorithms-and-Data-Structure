#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

class customStack {
 private:
    int *stack;
    int count;

 public:
    customStack();

    void push(int item);

    string pop();

    string back();

    [[nodiscard]] int size() const;

    // Деструктор - освобождает память
    ~customStack();

    void clear();

    static void exit();
};


void customStack::exit() {
    std::cout << "bye" << "\n";
}

void customStack::clear() {
    delete[] stack;
    stack = new int[10000];
    count = 0;
    cout << "ok" << "\n";
}

customStack::~customStack() {
    if (count > 0) {
        delete[] stack;
    }
}

string customStack::back() {
    if (count == 0) {
        // стек пуст
        return "error";
    } else {
        return std::to_string(stack[count - 1]);
    }
}

string customStack::pop() {
    if (count == 0) {
        // стек пуст
        return "error";
    } else {
        count--;
        return std::to_string(stack[count]);
    }
}

void customStack::push(int item) {
    // блок try необходим для перехвата исключения, если память не выделится
    try {
        // добавить последний элемент
        stack[count] = item;
        count++;
        cout << "ok" << "\n";
    }
    catch (std::bad_alloc &e) {
        cout << e.what() << "\n";
    }
}

customStack::customStack() {
    stack = new int[10000];
    count = 0;
}

int customStack::size() const  {
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string input;
    int digit;
    customStack cs = *new customStack();
    while (input != "exit") {
        cin >> input;
        if (input == "push") {
            cin >> digit;
            cs.push(digit);
        } else if (input == "pop") {
            cout << cs.pop() << "\n";
        } else if (input == "back") {
            cout << cs.back() << "\n";
        } else if (input == "size") {
            cout << cs.size() << "\n";
        } else if (input == "clear") {
            cs.clear();
        } else if (input == "exit") {
            customStack::exit();
            break;
        }
    }
    return 0;
}
