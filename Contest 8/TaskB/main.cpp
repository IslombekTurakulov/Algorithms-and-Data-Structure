// Использовал следующие источники:
// https://neerc.ifmo.ru/wiki/index.php?title=B-дерево
// https://neerc.ifmo.ru/wiki/index.php?title=B%2B-дерево
// https://www.bluerwhite.org/btree/

#include <iostream>

struct Node {
    int size;
    bool leaf;
    int *keys;
    Node **childs;
    Node *parent;
    Node *right;
    Node *left;

    explicit Node(int t_degree) {
        leaf = true;
        size = 0;
        keys = new int[2 * t_degree - 1]();
        childs = new Node *[2 * t_degree]();
        parent = nullptr;
        right = nullptr;
        left = nullptr;
    }

    ~Node() {
        for (int index = 0; index < size + 1; ++index) {
            delete childs[index];
        }
        delete[] keys;
        delete[] childs;
    }
};

class BPlusTree {
public:
    explicit BPlusTree(int degree);

    ~BPlusTree();

    void insert(int key);

    void printLeaves() const;

private:
    Node *root_;
    int t_;

    void splitNode(Node *root, Node *node) {
        auto node_new = new Node(t_);
        node_new->right = node->right;
        node->right = node_new;
        node->right->left = node_new;
        node_new->left = node;
        int mid_key = node->keys[t_ - 1];
        node_new->size = t_ - 1;
        node->size = t_ - 1;
        for (int index_i = 0; index_i < node_new->size - 1; ++index_i) {
            node_new->keys[index_i] = node->keys[index_i + t_ + 1];
            node_new->childs[index_i] = node->childs[index_i + t_ + 1];
        }
        node_new->childs[node_new->size] = node->childs[2 * t_ - 1];
        if (node->leaf) {
            ++node_new->size;
            node_new->leaf = true;
            for (int index_i = node_new->size - 1; index_i > 0; --index_i) {
                node_new->keys[index_i] = node->keys[index_i - 1];
            }
            node_new->keys[0] = node->keys[t_ - 1];
        }
        if (node == root) {
            root = new Node(t_);
            root->keys[0] = mid_key;
            root->childs[0] = node;
            root->childs[1] = node_new;
            root->size = 1;
            node->parent = root;
            node_new->parent = root;
            root_ = root;
        } else {
            node_new->parent = node->parent;
            if (!node->parent) {
                node->parent = new Node(t_);
            }
            auto parent = node->parent;
            int index_i = parent->size;
            for (; index_i > 0; --index_i) {
                if (mid_key > node->keys[index_i - 1]) {
                    break;
                }
                parent->keys[index_i] = parent->keys[index_i - 1];
                parent->childs[index_i + 1] = parent->childs[index_i];
            }
            parent->keys[index_i] = mid_key;
            parent->childs[index_i + 1] = node_new;
            ++parent->size;
            if (parent->size == 2 * t_ - 1) {
                splitNode(root, parent);
            }
        }
    }

    static Node *findLeaf(Node *node, int key) {
        while (!node->leaf) {
            for (int index = 0; index <= node->size; ++index) {
                if (key == node->keys[index]) {
                    return nullptr;
                }
                if (index == node->size || key < node->keys[index]) {
                    node = node->childs[index];
                    break;
                }
            }
        }
        return node;
    }

    void printRec(Node *node) const;
};

BPlusTree::BPlusTree(int degree) {
    root_ = nullptr;
    t_ = degree;
}

BPlusTree::~BPlusTree() {
    delete root_;
}

void BPlusTree::insert(int key) {
    if (!root_) {
        auto node = new Node(t_);
        node->keys[0] = key;
        ++node->size;
        root_ = node;
    } else {
        auto leaf = findLeaf(root_, key);
        if (!leaf) {
            return;
        }
        int index_i = 0;
        while (index_i < leaf->size && leaf->keys[index_i] < key) {
            ++index_i;
        }
        for (int index = leaf->size; index > index_i; --index) {
            leaf->keys[index] = leaf->keys[index - 1];
        }
        leaf->keys[index_i] = key;
        ++leaf->size;
        if (root_->size == 2 * t_ - 1) {
            splitNode(root_, leaf);
        }
    }
}

void BPlusTree::printLeaves() const {
    printRec(this->root_);
}

void BPlusTree::printRec(Node *node) const {
    if (!node) {
        return;
    } else {
        for (int index = 0; index < node->size + 1; ++index) {
            printRec(node->childs[index]);
        }
        for (int index = 0; index < node->size && node->leaf; ++index) {
            std::cout << node->keys[index] << " ";
            if (index + 1 == node->size) {
                std::cout << "\n";
            }
        }
    }
}
