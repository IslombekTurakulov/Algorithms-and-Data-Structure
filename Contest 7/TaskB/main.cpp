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

int maxValue(TreeNode *root) {
    int second_max;
    auto previous = root;
    auto current = root;
    for (; current->right_;) {
        previous = current;
        current = current->right_;
    }
    if (!current->left_) {
        second_max = current == root && previous == root ? 0 : previous->data_;
    } else {
        current = current->left_;
        for (; current->right_;) {
            current = current->right_;
        }
        second_max = current->data_;
    }
    return second_max;
}

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
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
    cout << maxValue(tree_node) << "\n";
    delete tree_node;
    return 0;
}
