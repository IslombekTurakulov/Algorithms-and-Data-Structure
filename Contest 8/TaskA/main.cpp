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

    explicit Node(int t_degree) {
        leaf = true;
        size = 0;
        keys = new int[2 * t_degree - 1]();
        childs = new Node *[2 * t_degree]();
    }

    ~Node() {
        for (int index = 0; index < size + 1; ++index) {
            delete childs[index];
        }
        delete[] keys;
        delete[] childs;
    }
};

class BTree {
public:
    explicit BTree(int degree);

    ~BTree();

    void insert(int key);

    size_t size() const;

    int64_t sum() const;

private:
    Node *root_;
    int t_;

    void splitNode(Node *node, int index, Node *temp) const {
        auto node_new = new Node(t_);
        node_new->leaf = temp->leaf;
        temp->size = t_ - 1;
        node_new->size = t_ - 1;
        int mid_key = temp->keys[temp->size];
        for (int index_i = 0; index_i < node_new->size; ++index_i) {
            node_new->keys[index_i] = temp->keys[index_i + temp->size + 1];
        }

        if (temp->leaf != true) {
            for (int index_i = 0; index_i < node_new->size + 1; ++index_i) {
                node_new->childs[index_i] = temp->childs[index_i + temp->size + 1];
            }
        }
        int index_i = node->size;
        for (; index_i > 0; --index_i) {
            if (mid_key > node->keys[index_i - 1]) {
                break;
            }
            node->keys[index_i] = node->keys[index_i - 1];
            node->childs[index_i + 1] = node->childs[index_i];
        }
        node->keys[index_i] = mid_key;
        node->childs[index_i + 1] = node->childs[index_i];
        ++node->size;

        node->childs[index + 1] = node_new;
    }

    Node *searchAndSplit(Node *node, int key) {
        while (node->leaf != true) {
            for (int index = 0; index < node->size + 1; ++index) {
                if (index == node->size || key < node->keys[index]) {
                    Node *temp = node->childs[index];
                    if (temp->size == 2 * t_ - 1) {
                        splitNode(node, index, temp);
                        if (node->keys[index] < key) {
                            temp = node->childs[index + 1];
                        }
                    }
                    node = temp;
                    break;
                }
            }
        }
        return node;
    }

    size_t getSize(Node *node) const {
        if (!node) {
            return 0;
        } else {
            size_t sum = 1;
            for (int index = 0; index < node->size + 1; ++index) {
                sum += getSize(node->childs[index]);
            }
            return sum;
        }
    }

    int64_t getSum(Node *node) const {
        if (!node) {
            return 0;
        } else {
            int64_t sum = 0;
            for (int index = 0; index < node->size && node->leaf; ++index) {
                sum += node->keys[index];
            }
            for (int index = 0; index < node->size + 1; ++index) {
                sum += getSum(node->childs[index]);
            }
            return sum;
        }
    }
};

BTree::BTree(int degree) {
    root_ = nullptr;
    t_ = degree;
}

BTree::~BTree() {
    delete root_;
}

void BTree::insert(int key) {
    if (!root_) {
        auto node = new Node(t_);
        node->keys[0] = key;
        ++node->size;
        root_ = node;
    } else {
        if (root_->size == 2 * t_ - 1) {
            Node *new_node = new Node(t_);
            new_node->leaf = false;
            new_node->childs[0] = root_;
            splitNode(new_node, 0, root_);
            root_ = new_node;
        }
        Node *leaf = searchAndSplit(root_, key);
        for (int index = 0; index < leaf->size; ++index) {
            if (key == leaf->keys[index]) {
                return;
            }
        }

        for (int index = leaf->size; index >= 0; --index) {
            if (index == 0 || key > leaf->keys[index - 1]) {
                leaf->keys[index] = key;
                break;
            }
            leaf->keys[index] = leaf->keys[index - 1];
        }
        ++leaf->size;
    }
}

size_t BTree::size() const {
    return getSize(this->root_);
}

int64_t BTree::sum() const {
    return getSum(this->root_);
}
