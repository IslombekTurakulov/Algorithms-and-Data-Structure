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

void printNodeWithNoDescendants(TreeNode *tree) {
    if (tree->left_ || tree->right_) {
        if (tree->left_) {
            printNodeWithNoDescendants(tree->left_);
        }
        if (!tree->right_) {
            return;
        }
        printNodeWithNoDescendants(tree->right_);
    } else {
        cout << tree->data_ << "\n";
    }
}

int maxValue(TreeNode *root) {
    TreeNode *current = root;
    while (current && current->right_) {
        current = current->right_;
    }
    if (current->left_) {
        if (root->data_ > current->left_->data_) {
            return root->data_;
        } else {
            return current->left_->data_;
        }
    } else {
        return root->data_;
    }
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
    printNodeWithNoDescendants(tree_node);
    delete tree_node;
    return 0;
}
