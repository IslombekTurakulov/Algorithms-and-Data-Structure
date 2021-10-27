#include <iostream>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::string;

class Calculation {
private:
    string symbol_;
    int64_t* arr_;
    int64_t* block_arr_;
    int64_t size_ = 0;
    int64_t capacity_ = 0;
    int64_t block_size_ = 0;

public:
    explicit Calculation(int64_t size_of_array, string symbol_input);

    ~Calculation();

    void insert(int64_t pos, int64_t value);

    void erase(int64_t pos);

    void build();

    void change(int64_t pos, int64_t value);

    int64_t at(int64_t pos);

    int64_t compute(int64_t left, int64_t right);

    int64_t getSize();

    int64_t moduleCalc(int64_t left, int64_t right, int64_t sum) const;

    int64_t xorCalc(int64_t left, int64_t right, int64_t sum) const;
};

void showChoice(const string& first_input, const int64_t mod_num, const int64_t requests,
                Calculation* calculation);

void fillArray(const int64_t size_of_array, Calculation* calculation);

Calculation::Calculation(int64_t size, string symbol) {
    symbol_ = symbol;
    capacity_ = size;
    arr_ = new int64_t[size];
    block_size_ = ceil(sqrt(size));
    block_arr_ = new int64_t[block_size_];
    size_ = 0;
}

void Calculation::insert(int64_t pos, int64_t value) {
    if (size_ >= capacity_) {
        capacity_ *= 2;
        auto* temp = new int64_t[capacity_]();
        for (int i = 0; i < size_; ++i) {
            temp[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = temp;
    }
    for (auto i = size_ - 1; i >= pos; --i) {
        arr_[i + 1] = arr_[i];
    }
    arr_[pos] = value;
    ++size_;
}

void Calculation::erase(int64_t pos) {
    for (int64_t c = pos; c < size_ - 1; c++) {
        arr_[c] = arr_[c + 1];
    }
    --size_;
}

void Calculation::change(int64_t pos, int64_t value) {
    block_size_ = ceil(sqrt(size_));
    int block_number = pos / block_size_;

    if (symbol_ == "+") {
        block_arr_[block_number] += value - arr_[pos];
    } else {
        block_arr_[block_number] ^= value ^ arr_[pos];
    }
    arr_[pos] = value;
}

int64_t Calculation::at(int64_t pos) {
    return arr_[pos];
}

int64_t Calculation::compute(int64_t left, int64_t right) {
    int64_t sum = 0;
    if (symbol_ == "+") {
        sum = moduleCalc(left, right, sum);
    } else {
        sum = xorCalc(left, right, sum);
    }
    return sum;
}

int64_t Calculation::xorCalc(int64_t left, int64_t right, int64_t sum) const {
    --right;
    for (; left <= right; ++left) {
        if (left % block_size_ == 0 && (left + block_size_) <= right) {
            sum ^= block_arr_[left / block_size_];
            left += block_size_ - 1;
        } else {
            sum ^= arr_[left];
        }
    }
    return sum;
}

int64_t Calculation::moduleCalc(int64_t left, int64_t right, int64_t sum) const {
    --right;
    for (; left <= right; ++left) {
        if (left % block_size_ == 0 && (left + block_size_) <= right) {
            sum += block_arr_[left / block_size_];
            left += block_size_ - 1;
        } else {
            sum += arr_[left];
        }
    }
    return sum;
}

int64_t Calculation::getSize() {
    return size_;
}

Calculation::~Calculation() {
    delete[] arr_;
    arr_ = nullptr;
    delete[] block_arr_;
    block_arr_ = nullptr;
    block_size_ = 0;
    size_ = 0;
}

void Calculation::build() {
    int block_id = -1;
    block_size_ = ceil(sqrt(size_));
    delete[] block_arr_;
    block_arr_ = new int64_t[block_size_]();
    for (int i = 0; i < size_; i++) {
        if (i % block_size_ == 0) {
            block_id++;
        }
        if (symbol_ == "+") {
            block_arr_[block_id] += arr_[i];
        } else {
            block_arr_[block_id] ^= arr_[i];
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string first_input;
    int64_t mod_num = 0;
    int64_t size_of_array = 0;
    int64_t requests = 0;
    cin >> first_input;
    if (first_input == "+") {
        cin >> mod_num;
    }
    cin >> size_of_array;
    Calculation* calculation = new Calculation(size_of_array, first_input);
    fillArray(size_of_array, calculation);
    cin >> requests;
    showChoice(first_input, mod_num, requests, calculation);
    delete calculation;
    return 0;
}

void fillArray(const int64_t size_of_array, Calculation* calculation) {
    for (int64_t i = 0; i < size_of_array; ++i) {
        int64_t input;
        cin >> input;
        calculation->insert(i, input);
    }
    calculation->build();
}

void showChoice(const string& first_input, const int64_t mod_num, const int64_t requests,
                Calculation* calculation) {
    bool is_changed = false;
    for (int64_t i = 0; i < requests; ++i) {
        string input_requests;
        cin >> input_requests;
        if (input_requests == "insert") {
            int64_t position, value;
            cin >> position >> value;
            calculation->insert(position - 1, value);
            is_changed = true;
        }
        if (input_requests == "erase") {
            int64_t position;
            cin >> position;
            calculation->erase(position - 1);
            is_changed = true;
        }
        if (input_requests == "change") {
            int64_t position, value;
            cin >> position >> value;
            calculation->change(position - 1, value);
        }
        if (input_requests == "at") {
            int64_t position;
            cin >> position;
            cout << calculation->at(position - 1) << "\n";
        }
        if (input_requests == "compute") {
            if (is_changed) {
                calculation->build();
                is_changed = false;
            }
            int64_t left, right;
            cin >> left >> right;
            int64_t result = calculation->compute(left - 1, right);
            if (first_input == "+") {
                cout << (result % mod_num + mod_num) % mod_num << "\n";
            } else {
                cout << result << "\n";
            }
        }
        if (input_requests == "size") {
            cout << calculation->getSize() << "\n";
        }
    }
}
