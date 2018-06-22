// 所有用例通过
#include <cstdio>

class node {
private:
    long long value;
    node * next;
public:
    node(long long _value):value(_value), next(NULL) { }

    void setNext(node * _next) {
        next = _next;
    }

    node * getNext() {
        return next;
    }

    long long getValue() {
        return value;
    }
};

class list {
private:
    node * head;
public:
    list(node * _head):head(_head) { }
    
    bool addIfExist(long long x) {
        if (head == NULL) {
            head = new node(x);
            return true;
        }
        node * tmp = head;
        while (true) {
            if (tmp->getValue() == x) {
                return false;
            } else {
                if (tmp->getNext() != NULL) {
                    tmp = tmp->getNext();
                } else {
                    tmp->setNext(new node(x));
                    return true;
                }
            }
        }
    }

    bool deleteIfExist(long long x) {
        if (head == NULL) {
            return false;
        }
        if (head->getValue() == x) {
            node * tmp = head;
            head = head->getNext();
            delete tmp;
            return true;
        }
        node * tmp = head;
        node * next = tmp->getNext();
        while(next != NULL) {
            if (next->getValue() == x) {
                tmp->setNext(next->getNext());
                delete next;
                return true;
            } else {
                tmp = next;
                next = tmp->getNext();
            }
        }
        return false;
    }

    // ~list() {
    //     if (head != NULL) {
    //         deleteNode(head);
    //     }
    // }
    // void deleteNode(node * n) {
    //     if (n->getNext() != NULL) {
    //         deleteNode(n->getNext());
    //     }
    //     delete n;
    // }
};

class hash {
private:
    static const long long HASH_FACTOR = 997L;
    list ** table;
public:
    hash() {
        table = new list * [HASH_FACTOR];
    }

    int hashNumber(long long x) {
        long long result = x % HASH_FACTOR;
        return result;
    }

    bool addIfExist(long long x) {
        int key = hashNumber(x);
        if (table[key] == NULL) {
            table[key] = new list(NULL);
        }
        return table[key]->addIfExist(x);
    }

    bool deleteIfExist(long long x) {
        int key = hashNumber(x);
        if (table[key] == NULL) {
            return false;
        }
        return table[key]->deleteIfExist(x);
    }
};

int main() {
    long n;
    scanf("%ld", &n);
    hash h;
    for (; n > 0; n--) {
        int op;
        scanf("%d", &op);
        long long x;
        scanf("%lld", &x);
        bool result;
        switch(op) {
            case 1:
                result = h.addIfExist(x);
                break;
            case 2:
                result = h.deleteIfExist(x);
                break;
        }
        if (result) {
            printf("Succeeded\n");
        } else {
            printf("Failed\n");
        }
    }

    return 0;
}