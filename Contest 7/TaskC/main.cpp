#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::max;
using std::string;

struct Node {
    TreeNode *value;
    Node *next, *prev;
};

class Deque {
    Node *top_, *tail_;
    int count_;

 public:
    Deque();

    ~Deque();

    void pushBack(TreeNode *num);

    void popBack();

    TreeNode *front();

    const int size() const;

    void clear();
};

Deque::Deque() {
    top_ = nullptr;
    tail_ = nullptr;
    count_ = 0;
}

void Deque::pushBack(TreeNode *num) {
    // выделение памяти под новый элемент структуры
    Node *node = new Node;
    node->value = num;
    count_++;
    if (top_ != nullptr) {
        node->prev = tail_;
        tail_->next = node;
        tail_ = node;
    } else {
        top_ = node;
        tail_ = top_;
    }
}

void Deque::popBack() {
    //если дек не пустой
    if (count_ != 0) {
        cout << tail_->value << "\n";
        if (count_ <= 1) {
            top_ = nullptr;
            tail_ = nullptr;
            count_--;
        } else {
            auto *node = tail_;
            tail_ = tail_->prev;
            tail_->next = nullptr;
            delete node;
            count_--;
        }
    } else {
        cout << "error"
             << "\n";
    }
}

TreeNode *Deque::front() {
    return top_->value;
}

const int Deque::size() const {
    return count_;
}

void Deque::clear() {
    count_ = 0;
    while (top_) {
        tail_ = top_->next;
        delete top_;
        top_ = tail_;
    }
}

Deque::~Deque() {
    clear();
}

struct TreeNode {
 public:
    TreeNode *right_;
    TreeNode *left_;
    int64_t data_;

    explicit TreeNode(int64_t data) {
        data_ = data;
        left_ = nullptr;
        right_ = nullptr;
    }

    ~TreeNode() {
        if (left_) {
            delete left_;
        }
        if (right_) {
            delete right_;
        }
    }
};

TreeNode *insert(TreeNode *root, int64_t data) {
    if (root == nullptr) {
        return new TreeNode(data);
    }
    if (data < root->data_) {
        root->left_ = insert(root->left_, data);
    } else {
        root->right_ = insert(root->right_, data);
    }
    return root;
}

bool search(TreeNode *root, int64_t key) {
    if (root == nullptr) {
        return false;
    }
    if (key == root->data_) {
        return true;
    }
    if (key < root->data_) {
        return search(root->left_, key);
    } else {
        return search(root->right_, key);
    }
}

void print(TreeNode *root) {
    if (!root) {
        return;
    }
    if (root->left_) {
        print(root->left_);
    }
    cout << root->data_ << "\n";
    if (root->right_) {
        print(root->right_);
    }
}

int main() {
    int64_t first;
    cin >> first;
    TreeNode *tree_node = new TreeNode(first);
    for (; first != 0;) {
        cin >> first;
        if (first != 0) {
            auto result = search(tree_node, first);
            if (!result) {
                tree_node = insert(tree_node, first);
            }
        }
    }
    print(tree_node);
    delete tree_node;
    return 0;
}
