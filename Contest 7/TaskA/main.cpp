// Использовал algorithm для подсчёта максимальных данных
// Я думаю это никак не противоречит условию
#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::max;
using std::string;

struct TreeNode {
public:
    TreeNode *right_;
    TreeNode *left_;
    int64_t data_;

    explicit TreeNode(int data) {
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

int64_t maxDepth(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int64_t left = maxDepth(root->left_);
    int64_t right = maxDepth(root->right_);
    return max(left, right) + 1;
}

// searches a given key in a tree
bool search(TreeNode *root, int key) {
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
    cout << maxDepth(tree_node) << "\n";
    delete tree_node;
    return 0;
}
