#include <cstdio>
#include <cstring>

class stack {
private:
    int size;
    int * array;
    int capacity;
    static const int FACTOR = 2;
    static const int SHRINK_FACTOR = 4;
    static const int INIT_CAPACITY = 8;
public:
    stack():size(0), capacity(INIT_CAPACITY) {
        array = new int[INIT_CAPACITY];
    }
    stack(int n):size(0), capacity(n) {
        array = new int[n];
    }

    void enlargeIfNeeded() {
        if (capacity < INIT_CAPACITY || size == capacity) {
            if (array) {
                int * tmpArray = new int[FACTOR * capacity];
                memcpy(tmpArray, array, sizeof(int) * size);
                delete [] array;
                array = tmpArray;
            } else {
                // something unusual happen
                array = new int[capacity];
                size = 0;
            }
        }
    }

    void shrinkIfNeeded() {
        if (capacity > INIT_CAPACITY && 
                size < capacity / SHRINK_FACTOR) {
            if (array) {
                int * tmpArray = new int[capacity / FACTOR];
                memcpy(tmpArray, array, sizeof(int) * size);
                delete [] array;
                array = tmpArray;
            }
        }
    }

    void push(int a) {
        enlargeIfNeeded();
        array[size++] = a;
    }

    int pop() {
        int tmp = array[--size];
        shrinkIfNeeded();
        return tmp;
    }

    int top() {
        if (size == 0) {
            return -1;
        }
        return array[size - 1];
    }

    bool empty() {
        return size == 0;
    }

    ~stack() {
        if (array) {
            delete [] array;
        }
    }
};

stack stacksort(stack & s) {
    stack result;
    if (s.empty()) {
        return result;
    }
    int tmp = s.pop();
    while(!s.empty() || 
            (!result.empty() && result.top() > tmp)) {
        if (result.empty() || result.top() <= tmp) {
            result.push(tmp);
            tmp = s.pop();
        } else {
            s.push(result.pop());
        }
    }
    result.push(tmp);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    stack s;
    for (; n > 0; n--) {
        int tmp;
        scanf("%d", &tmp);
        s.push(tmp);
    }
    stack result = stacksort(s);
    while(!result.empty()) {
        printf("%d\n", result.pop());
    }
    return 0;
}