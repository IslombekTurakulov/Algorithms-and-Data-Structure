#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::to_string;

template<class T>
struct Node {
    // Следующая ячейка
    Node *next;
    // Значение
    T value;

    explicit Node(T value) {
        this->next = nullptr;
        this->value = value;
    }
};

template<class T>
struct CustomQueue {
    // Количество элементов
    int count;
    // Первая ячейка
    Node<T> *first_node;
    // Последняя ячейка
    Node<T> *last_node;
    // Ячейка в центре
    Node<T> *middle_node;

    // Конструктор без параметров, задаём значения по умолчанию
    CustomQueue();

    void push_value(T value);

    void push_to_middle(T value);

    T pop_elements();

    void Clear();
};

template<class T>
CustomQueue<T>::CustomQueue() {
    count = 0;
    first_node = nullptr;
    last_node = nullptr;
    middle_node = nullptr;
}

template<class T>
void CustomQueue<T>::push_value(T value) {
    // Новая ячейка
    auto *temp = new Node<T>(value);
    // Если очередь не пустая
    if (count > 0) {
        // след last_node ячейкой будет новая ячейка
        last_node->next = temp;
        last_node = temp;
        // last_node будет теперь указана на новой ячейке
        if (count % 2 == 0) {
            middle_node = middle_node->next;
        }
    } else {
        first_node = temp;
        last_node = temp;
        middle_node = temp;
    }
    count++;
}

template<class T>
void CustomQueue<T>::push_to_middle(T value) {
    // Если количество элементов не пустое
    if (count <= 1) {
        push_value(value);
    } else {
        auto *temp = new Node<T>(value);
        temp->next = middle_node->next;
        middle_node->next = temp;
        if (count % 2 == 0) {
            middle_node = temp;
        }
        count++;
    }
}

template<class T>
T CustomQueue<T>::pop_elements() {
    // Делаем копию значения
    T temp = first_node->value;
    // Сохраняем указатель на ячейку которая удалится
    Node<T> *node_to_delete = first_node;
    // Первым элементом (first_node) будет следующая ячейка
    first_node = first_node->next;

    if (count % 2 == 0 && count > 1) {
        middle_node = middle_node->next;
    } else if (count == 1) {
        middle_node = nullptr;
    }
    count--;
    // удаляем старую ячейку, которая ненужна
    delete node_to_delete;
    return temp;
}

template<class T>
void CustomQueue<T>::Clear() {
    Node<T> *temp = first_node;
    Node<T> *next;
    //удаляем ячейки, пока не удалим все
    while (temp != nullptr) {
        next = temp->next;
        delete temp;
        temp = next;
    }
    first_node = nullptr;
    last_node = nullptr;
    count = 0;
}

int main() {
    // https://codeforces.com/blog/entry/5217?locale=ru
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int input;
    cin >> input;
    CustomQueue<int> custom_queue;
    char symbol;
    for (int i = 0; i < input; i++) {
        cin >> symbol;
        if (symbol != '+') {
            if (symbol == '-') {
                cout << custom_queue.pop_elements() << '\n';
            } else {
                if (symbol != '*') {
                    continue;
                }
                int temp_value;
                cin >> temp_value;
                custom_queue.push_to_middle(temp_value);
            }
        } else {
            int temp_value;
            cin >> temp_value;
            custom_queue.push_value(temp_value);
        }
    }
    custom_queue.Clear();
    return 0;
}
