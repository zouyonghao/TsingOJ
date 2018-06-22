// 所有用例通过
#include <iostream>
#include <cstring>
using namespace std;

class queue {
private:
    string * array;
    int size;
    int capacity;
    static const int INIT_CAPACITY = 8;
    static const int FACTOR = 2;

public:
    queue():size(0), capacity(INIT_CAPACITY) {
        array = new string[INIT_CAPACITY];
    }

    queue(int _capacity):size(0) {
        capacity = _capacity > INIT_CAPACITY ? _capacity : INIT_CAPACITY;
        array = new string[capacity];
    }

    ~queue() {
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

    void enqueue(string str) {
        array[size++] = str;
        expand();
    }

    string dequeue() {
        string tmp = head();
        if (size > 0) {
            for (int i = 1; i < size; i++) {
                array[i - 1] = array[i];
            }
            size--;
        }
        shrink();
        return tmp;
    }

    string head() {
        if (size > 0) {
            return array[0];
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
    queue s;
    for (; n > 0; n--) {
        int op;
        cin >> op;
        switch(op) {
            case 1: {
                string str;
                cin >> str;
                s.enqueue(str);
                break;
            }
            case 2:
                cout << s.dequeue() << endl;
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