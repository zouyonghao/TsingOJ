// 所有用例通过
#include <iostream>
#include <cstring>
using namespace std;

class stack {
private:
    string * array;
    int size;
    int capacity;
    static const int INIT_CAPACITY = 8;
    static const int FACTOR = 2;

public:
    stack():size(0), capacity(INIT_CAPACITY) {
        array = new string[INIT_CAPACITY];
    }

    stack(int _capacity):size(0) {
        capacity = _capacity > INIT_CAPACITY ? _capacity : INIT_CAPACITY;
        array = new string[capacity];
    }

    ~stack() {
        delete [] array;
    }

    void expand() {
        if (size == capacity) {
            capacity *= FACTOR;
            string * tmp = new string[capacity];
            for (int i = 0; i < size; i++) {
                tmp[i] = array[i];
            }
            delete [] array;
            array = tmp;
        }
    }

    void shrink() {
        if (capacity > INIT_CAPACITY && size < capacity / FACTOR / FACTOR) {
            capacity /= FACTOR;
            string * tmp = new string[capacity];
            for (int i = 0; i < size; i++) {
                tmp[i] = array[i];
            }
            delete [] array;
            array = tmp;
        }
    }

    void push(string str) {
        array[size++] = str;
        expand();
    }

    string pop() {
        string tmp = top();
        if (size > 0) {
            size--;
        }
        shrink();
        return tmp;
    }

    string top() {
        if (size > 0) {
            return array[size - 1];
        }
        return NULL;
    }

    string get(int index) {
        return array[index - 1];
    }

};

int main() {
    int n;
    cin >> n;
    stack s;
    for (; n > 0; n--) {
        int op;
        cin >> op;
        switch(op) {
            case 1: {
                string str;
                cin >> str;
                s.push(str);
                break;
            }
            case 2:
                cout << s.pop() << endl;
                break;
            case 3:
                int index;
                cin >> index;
                cout << s.get(index) << endl;
                break;
        }
    }
    return 0;
}