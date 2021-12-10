#include <iostream>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType key, ValueType value) {
        key_ = key;
        value_ = value;
        next_ = nullptr;
    }
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
    Node<KeyType, ValueType> **table_ = nullptr;
    size_t capacity_{};
    size_t size_{};
    double coefficient_{};
    Func hasher_;

    void rehashing() {
        size_t old_capacity = capacity_;
        if (capacity_ * 2 < UINT64_MAX) {
            capacity_ *= 2;
        }
        Node<KeyType, ValueType> **temp_table = table_;
        table_ = new Node<KeyType, ValueType> *[capacity_]();
        size_ = 0;
        for (uint64_t i = 0; i < old_capacity; ++i) {
            Node<KeyType, ValueType> *current = temp_table[i];
            if (current != nullptr) {
                while (current != nullptr) {
                    Node<KeyType, ValueType> *prev = current;
                    insert(prev->key_, prev->value_);
                    current = current->next_;
                    delete prev;
                }
            }
        }
        delete[] temp_table;
    }

public:
    HashTable() {
        this->table_ = new Node<KeyType, ValueType> *[100]();
        for (uint64_t i = 0; i < 100; ++i) {
            table_[i] = nullptr;
        }
        this->capacity_ = 100;
        this->coefficient_ = 0.5;
        this->size_ = 0;
    }

    explicit HashTable(Func func) {
        this->hasher_ = func;
        this->table_ = new Node<KeyType, ValueType> *[100]();
        for (uint64_t i = 0; i < 100; ++i) {
            table_[i] = nullptr;
        }
        this->capacity_ = 100;
        this->coefficient_ = 0.5;
        this->size_ = 0;
    }

    HashTable(size_t capacity, double coeff, Func = std::hash<KeyType>()) {
        if (capacity <= 0) {
            capacity_ = 50;
            capacity = 50;
        }
        this->capacity_ = capacity;
        this->table_ = new Node<KeyType, ValueType> *[capacity]();
        for (uint64_t i = 0; i < this->capacity_; ++i) {
            table_[i] = nullptr;
        }
        if (coeff > 0 && coeff <= 1) {
            this->coefficient_ = coeff;
        } else {
            this->coefficient_ = 0.5;
        }
        this->size_ = 0;
    }

    ~HashTable() {
        for (uint64_t i = 0; i < capacity_; ++i) {
            Node<KeyType, ValueType> *current = table_[i];
            if (current != nullptr) {
                while (current != nullptr) {
                    Node<KeyType, ValueType> *prev = current;
                    current = current->next_;
                    delete prev;
                }
            }
        }
        delete[] table_;
    }

    void insert(KeyType key, ValueType value) {
        size_t index = this->hasher_(key) % capacity_;
        if (index >= 0 && index < capacity_) {
            Node<KeyType, ValueType> *previous = nullptr;
            Node<KeyType, ValueType> *current = table_[index];
            while (current != nullptr && current->key_ != key) {
                previous = current;
                current = current->next_;
            }
            if (current == nullptr) {
                current = new Node<KeyType, ValueType>(key, value);
                if (previous == nullptr) {
                    table_[index] = current;
                } else {
                    previous->next_ = current;
                }
                ++size_;
            } else {
                current->value_ = value;
            }
        }
        auto size_double = static_cast<double>(size_);
        if (size_double / capacity_ > coefficient_) {
            rehashing();
        }
    }

    ValueType *find(KeyType key) {
        size_t index = this->hasher_(key) % capacity_;
        if (index < 0 || index >= capacity_) {
            return nullptr;
        }
        if (table_[index]) {
            Node<KeyType, ValueType> *current = table_[index];
            while (current) {
                if (current->key_ == key) {
                    return &current->value_;
                }
                current = current->next_;
            }
        }
        return nullptr;
    }

    void erase(KeyType key) {
        size_t index = this->hasher_(key) % capacity_;
        if (index < 0 || index >= capacity_) {
            return;
        }
        if (table_[index]) {
            Node<KeyType, ValueType> *prev = nullptr;
            Node<KeyType, ValueType> *current = table_[index];
            while (current != nullptr && current->key_ != key) {
                prev = current;
                current = current->next_;
            }
            if (current == nullptr) {
                return;
            } else {
                if (prev == nullptr) {
                    table_[index] = current->next_;
                } else {
                    prev->next_ = current->next_;
                }
                delete current;
            }
            --size_;
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t index) {
        if (index < 0 || index >= capacity_) {
            throw std::out_of_range("");
        }
        Node<KeyType, ValueType> *current = table_[index];
        if (current == nullptr) {
            throw std::runtime_error("");
        }
        return *current;
    }

    Node<KeyType, ValueType> at(uint64_t index) {
        if (index < 0 || index >= capacity_) {
            throw std::out_of_range("");
        }
        Node<KeyType, ValueType> *current = table_[index];
        if (current == nullptr) {
            throw std::runtime_error("");
        }
        return *current;
    }

    size_t size() const {
        return this->size_;
    }

    size_t capacity() const {
        return this->capacity_;
    }
};
