// 所有用例通过
#include <iostream>
using namespace std;

class node {
private:
    int value;
    node * parent;
    node * left;
    node * right;
public:
    node():value(-1), parent(NULL), left(NULL), right(NULL) { }
    node(int _value):value(_value), parent(NULL), left(NULL), right(NULL) { }
    node(int _value, node * _parent, node * _left, node * _right)
        :value(_value), parent(_parent), left(_left), right(_right) { }
    
    int getValue() {
        return value;
    }

    node * getParent() {
        return parent;
    }
    void setParent(node * _parent) {
        parent = _parent;
    }
    node * getLeft() {
        return left;
    }
    void setLeft(node * _left) {
        left = _left;
    }
    node * getRight() {
        return right;
    }
    void setRight(node * _right) {
        right = _right;
    }
};

class tree {
private:
    node * head;
public:
    tree():head(NULL) { }
    tree(node * _head):head(_head) { }
    tree(int value) {
        head = new node(value);
    }
    ~tree() {
        deleteAll(head);
    }
    void deleteAll(node * head) {
        if (head == NULL) {
            return;
        }
        if (head->getLeft() != NULL) {
            deleteAll(head->getLeft());
        }
        if (head->getRight() != NULL) {
            deleteAll(head->getRight());
        }
        delete head;
    }

    void addNode(node * node) {
        if (head == NULL) {
            head = node;
        } else {
            addNode(node, head);
        }
    }

    void addNode(node * current, node * tree) {
        if (current->getValue() >= tree->getValue()) {
            if (tree->getRight() != NULL) {
                addNode(current, tree->getRight());
            } else {
                tree->setRight(current);
                current->setParent(tree);
            }
        } else {
            if (tree->getLeft() != NULL) {
                addNode(current, tree->getLeft());
            } else {
                tree->setLeft(current);
                current->setParent(tree);
            }
        }
    }

    void printPreorder() {
        printPreorder(head);
    }
    void printPreorder(node * tree) {
        if (tree == NULL) {
            return;
        }
        cout << tree-> getValue() << ' ';
        printPreorder(tree->getLeft());
        printPreorder(tree->getRight());
    }
    void printPostorder() {
        printPostorder(head);
    }
    void printPostorder(node * tree) {
        if (tree == NULL) {
            return;
        }
        printPostorder(tree->getLeft());
        printPostorder(tree->getRight());
        cout << tree-> getValue() << ' ';
    }
};

int main() {
    int n;
    cin >> n;
    tree t;
    for (; n > 0; n--) {
        int tmp;
        cin >> tmp;
        node * current = new node(tmp);
        t.addNode(current);
    }
    t.printPreorder();
    cout << endl;
    t.printPostorder();
    return 0;
}