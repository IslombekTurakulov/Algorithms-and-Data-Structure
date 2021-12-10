// Использовал следующие источники
// http://neerc.ifmo.ru/wiki/index.php?title=Splay-дерево
// https://ru.m.wikipedia.org/wiki/Splay-дерево

#include <algorithm>
#include <iostream>

struct Node {
    Node *left, *right, *parent;
    int key;

    explicit Node(int data) {
        key = data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class SplayTree {
    void zag(Node *node) {
        // Left rotation
        Node *temp = node->right;
        node->right = temp->left;
        if (temp->left) {
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            this->root_ = temp;
        } else if (node == node->parent->left) {
            node->parent->left = temp;
        } else if (node == node->parent->right) {
            node->parent->right = temp;
        }
        temp->left = node;
        node->parent = temp;
    }

    void zig(Node *node) {
        // Right rotation
        Node *temp = node->left;
        node->left = temp->right;
        if (temp->right) {
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == nullptr) {
            this->root_ = temp;
        } else if (node == node->parent->left) {
            node->parent->left = temp;
        } else if (node == node->parent->right) {
            node->parent->right = temp;
        }
        temp->right = node;
        node->parent = temp;
    }

    int maxHeight(Node *root) const {
        if (root == nullptr) {
            return 0;
        }
        return std::max(maxHeight(root->left), maxHeight(root->right)) + 1;
    }

    Node *root_;

public:
    SplayTree();

    ~SplayTree();

    void insert(int);

    Node *find(int key);

    int splay(Node *node);

    int getHeight() const;
};

SplayTree::SplayTree() {
    root_ = nullptr;
}

SplayTree::~SplayTree() {
    delete root_;
}

void SplayTree::insert(int value) {
    Node *pre_insert_place = nullptr;
    Node *insert_place = root_;
    while (insert_place != nullptr) {
        pre_insert_place = insert_place;
        if (insert_place->key < value) {
            insert_place = insert_place->right;
        } else if (value < insert_place->key) {
            insert_place = insert_place->left;
        } else {
            return;
        }
    }
    Node *insert_element = new Node(value);
    insert_element->parent = pre_insert_place;
    if (pre_insert_place == nullptr) {
        root_ = insert_element;
    } else if (pre_insert_place->key < insert_element->key) {
        pre_insert_place->right = insert_element;
    } else if (insert_element->key < pre_insert_place->key) {
        pre_insert_place->left = insert_element;
    } else {
        return;
    }
}

Node *SplayTree::find(int key) {
    Node *node = root_;
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return node;
        }
    }
    delete node;
    return nullptr;
}

int SplayTree::splay(Node *node) {
    int rotates_amount = 0;
    if (node != nullptr) {
        while (node->parent) {
            bool parent_left = node == node->parent->left;
            bool parent_right = node == node->parent->right;
            if (node->parent->parent != nullptr) {
                bool parent_parent_left = node->parent == node->parent->parent->left;
                if (!parent_left || !parent_parent_left) {
                    bool parent_parent_right = node->parent == node->parent->parent->right;
                    if (parent_right && parent_parent_right) {
                        zag(node->parent->parent);
                        zag(node->parent);
                        ++rotates_amount;
                        ++rotates_amount;
                        continue;
                    }
                    if (parent_right && parent_parent_left) {
                        zag(node->parent);
                        zig(node->parent);
                        ++rotates_amount;
                        continue;
                    }
                    if (parent_left && parent_parent_right) {
                        zig(node->parent);
                        zag(node->parent);
                        ++rotates_amount;
                    }
                } else {
                    zig(node->parent->parent);
                    zig(node->parent);
                    ++rotates_amount;
                    ++rotates_amount;
                }
            } else if (parent_left) {
                zig(node->parent);
                ++rotates_amount;
            } else if (parent_right) {
                zag(node->parent);
                ++rotates_amount;
            }
        }
        return rotates_amount;
    } else {
        return rotates_amount;
    }
}

int SplayTree::getHeight() const {
    return std::max(maxHeight(root_->left), maxHeight(root_->right));
}
