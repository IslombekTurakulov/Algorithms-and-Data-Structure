#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

class customStack {
    char *stack;
    int count;
    int capacity;

 public:
    customStack();

    void push(char item);

    char pop();

    [[nodiscard]] int size() const;

    // Деструктор - освобождает память
    ~customStack();

    void clear();
};

customStack::customStack() {
    capacity = 2;
    stack = new char[10];
    count = 0;
}

void customStack::push(char item) {
    if (count >= capacity) {
        capacity *= 2;
        char *new_arr = new char[capacity];

        for (int i = 0; i < count; i++) {
            new_arr[i] = stack[i];
        }
        delete[] stack;
        stack = new_arr;
    }
    if (stack == nullptr) {
        stack = new char[10];
    }
    stack[count] = item;
    count++;
}

char customStack::pop() {
    if (count != 0) {
        count--;
        return stack[count];
    }
}

int customStack::size() const {
    return count;
}

customStack::~customStack() {
    if (count > 0) {
        delete[] stack;
    }
}

void customStack::clear() {
    delete[] stack;
    stack = nullptr;
    count = 0;
}

bool calculateSymbols(customStack *cs, const string &input);

int main() {
    customStack cs;
    string input, size_of_results;
    getline(cin, input);
    cout << (calculateSymbols(&cs, input) ? "yes" : "no");
    cs.clear();
    return 0;
}

bool calculateSymbols(customStack *cs, const string &input) {
    for (const char i : input) {
        if (i == '(' || i == '{' || i == '[') {
            cs->push(i);
        } else {
            if (cs->size() == 0) {
                return false;
            }
            char current_char = cs->pop();
            if (current_char == '(') {
                if (i != ')') {
                    return false;
                }
            }
            if (current_char == '[') {
                if (i != ']') {
                    return false;
                }
            }
            if (current_char == '{') {
                if (i != '}') {
                    return false;
                }
            }
        }
    }
    return cs->size() == 0;
}
