#include <iostream>
#include "stdio.h"

struct Point {
    Point(int i, int i1, int value) {
        x = i;
        y = i1;
        v = value;
    }

    Point() {}

    int x, y, v;
};

class Stack {
    Point points[500];
    int size;
    int sum;
    int n;
    int *y;
public:
    Stack(int nn) {
        sum = 0;
        size = 0;
        n = nn;
        y = new int[n];
        for (int i = 0; i < n; i++) {
            y[i] = 0;
        }
    }

    virtual ~Stack() {
        delete[] y;
    }

    void push(Point p) {
        points[size++] = p;
        sum += p.v;
        *(y + p.y) = 1;
    }

    Point *pop() {
        if (!empty()) {
            Point p = points[size - 1];
            size--;
            sum -= p.v;
            *(y + p.y) = 0;
            return &p;
        }
        return NULL;
    }

    bool empty() {
        return size == 0;
    }

    Point *getTop() {
        if (!empty()) {
            return &points[size - 1];
        }
        return NULL;
    }

    int getNextY(int start) {
        for (int i = start; i < n; i++) {
            if (y[i] == 0) {
                return i;
            }
        }
        return -1;
    }

    int countSum() {
        return sum;
    }
};

int getSumByStack(int n, int **line_numbers);

int getSumByBacktracking(int n, int **pInt);

int main() {
    int n;
    std::cin >> n;
    if (n <= 0) {
        std::cout << 0;
        return 0;
    }
    int **line_numbers = new int *[n];
    for (int i = 0; i < n; i++) {
        line_numbers[i] = new int[n];
        for (int j = 0; j < n; j++) {
            std::cin >> line_numbers[i][j];
        }
    }
    int sum;
    // sum = getSumByStack(n, line_numbers);
    sum = getSumByBacktracking(n, line_numbers);

    std::cout << sum;
    return 0;
}

int getSumByStack(int n, int **line_numbers) {
    Stack stack(n);
    stack.push(Point(0, 0, line_numbers[0][0]));

    int sum = -1;
    while (!stack.empty()) {
        Point *top = stack.getTop();
        if (top->x == n - 1) {
            int currentSum = stack.countSum();
            if (sum > currentSum || sum == -1) {
                sum = currentSum;
            }
            stack.pop();
            top = stack.getTop();
            while (top != NULL) {
                int y = stack.getNextY(top->y + 1);
                if (y != -1) {
                    stack.pop();
                    stack.push(Point(top->x, y, line_numbers[top->x][y]));
                    break;
                }
                stack.pop();
                top = stack.getTop();
            }
        } else {
            int y = stack.getNextY(0);
            stack.push(Point(top->x + 1, y, line_numbers[top->x + 1][y]));
        }
    }
    return sum;
}


int cost = 0;
int *works;

void work(int n, int i, int count, int **line_numbers) {
    if (i >= n && count < cost) {
        cost = count;
        return;
    }
    if (count < cost) {
        for (int j = 0; j < n; j++) {
            if (works[j] != 1) {
                works[j] = 1;
                work(n, i + 1, count + line_numbers[i][j], line_numbers);
                works[j] = 0;
            }
        }
    }
}

int getSumByBacktracking(int n, int **pInt) {
    works = new int[n];
    for (int i = 0; i < n; i++) {
        works[i] = 0;
        cost += pInt[i][i];
    }
    work(n, 0, 0, pInt);
    delete[] works;
    return cost;
}
