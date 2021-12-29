#include <iostream>
#include <string>

template<typename T>
class Node {
private:
    Node<T> *next_node_, *prev_node_;
    T value_of_node_;

public:
    explicit Node(T value) {
        next_node_ = nullptr;
        prev_node_ = nullptr;
        value_of_node_ = value;
    }

    [[nodiscard]] T getData() const {
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

template<typename T>
class List {
private:
    Node<T> *head_node_;
    Node<T> *tail_node_;
    int length_of_node_;

public:
    List() {
        head_node_ = nullptr;
        length_of_node_ = 0;
    }

    void pushBack(T num) {
        auto *new_node = new Node<T>(num);
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

    void pushFront(T num) {
        auto *new_node = new Node<T>(num);
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

    void insert(T num, int position) {
        if (position == length_of_node_ - 1) {
            pushBack(num);
            return;
        }
        if (position == -1) {
            pushFront(num);
            return;
        }
        Node<T> *new_node = new Node<T>(num), *value = head_node_;
        for (int i = 0; value && i < position; ++i) {
            value = value->getNext();
        }
        new_node->setNext(value->getNext());
        new_node->setPrev(value);
        value->getNext()->setPrev(new_node);
        value->setNext(new_node);
        ++length_of_node_;
    }

    void remove(T position) {
        Node<T> *value_element = head_node_;
        for (int i = 0; i <= position; ++i) {
            value_element = value_element->getNext();
        }
        if (value_element->getPrev() == nullptr) {
            Node<T> *front = head_node_->getNext();
            if (front->getNext() != nullptr) {
                front->setPrev(nullptr);
            }
            delete head_node_;
            head_node_ = front;
        } else if (value_element->getNext() == nullptr) {
            Node<T> *back = tail_node_->getPrev();
            if (back != nullptr) {
                back->setNext(nullptr);
            }
            tail_node_->setPrev(nullptr);
            delete tail_node_;
            tail_node_ = back;
        } else {
            Node<T> *next = value_element->getNext();
            Node<T> *prev = value_element->getPrev();
            next->setPrev(prev);
            prev->setNext(next);
            value_element->setNext(nullptr);
            value_element->setPrev(nullptr);
            delete value_element;
        }
        --length_of_node_;
    }

    bool find(T data) {
        Node<T> *current = head_node_;
        while (current) {
            if (current->getData() != data) {
                current = current->getNext();
            } else {
                return true;
            }
        }
        return false;
    }

    ~List() {
        Node<T> *node;
        while (head_node_ != nullptr) {
            node = head_node_->getNext();
            delete head_node_;
            head_node_ = node;
        }
    }
};

// основной класс фильтра
class BloomFilter {
private:
    bool *filter_;
    List<std::string> *list_;
    size_t hashes_;
    size_t bits_;
    size_t valid_hashes_;
    size_t invalid_hashes_;

public:
    BloomFilter(size_t hashes, size_t bits) {
        this->filter_ = new bool[bits]();
        this->list_ = new List<std::string>();
        this->hashes_ = hashes;
        this->bits_ = bits;
        this->valid_hashes_ = 0;
        this->invalid_hashes_ = 0;
    }

    ~BloomFilter() {
        delete[] this->filter_;
        delete this->list_;
    }

    // вставка информации об объекте
    void add(const std::string &obj) {
        this->list_->pushBack(obj);
        size_t index = 0;
        while (index < this->hashes_) {
            if (index != 0) {
                size_t value = std::hash<std::string>{}(obj + std::to_string(index));
                this->filter_[value % this->bits_] = true;
            } else {
                size_t value = std::hash<std::string>{}(obj + "");
                this->filter_[value % this->bits_] = true;
            }
            ++index;
        }
    }

    // проверка принадлежности объекта
    bool verify(const std::string &obj) {
        size_t index = 0;
        ++this->valid_hashes_;
        while (index < this->hashes_) {
            auto key = obj + (index != 0 ? std::to_string(index) : "");
            size_t value = std::hash<std::string>{}(key);
            if (!this->filter_[value % this->bits_]) {
                return false;
            }
            ++index;
        }
        if (!this->list_->find(obj)) {
            ++this->invalid_hashes_;
            return true;
        } else {
            return true;
        }
    }

    // считаем относительную величину false positive rate по запросам тестирования
    // принадлежности
    [[nodiscard]] double getFPRate() const {
        if (this->valid_hashes_ == 0) {
            return 0;
        } else {
            return static_cast<double>(this->invalid_hashes_) / this->valid_hashes_;
        }
    }

    [[nodiscard]] size_t numberOfHashFunctions() const {
        return this->hashes_;
    }

    [[nodiscard]] size_t numberOfBits() const {
        return this->bits_;
    }
};