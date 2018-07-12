// Input
// The first line contains two integers: n (size of S) and m (the number of
// queries). The second line enumerates all the n points in S. Each of the
// following m lines consists of two integers a and b and defines an query
// interval [a, b]. Output The number of points in S lying inside each of the m
// query intervals. Example Input 5 2 1 3 7 9 11 4 6 7 12 Output
// 0
// 3

// time limit exceeded

#include <stdio.h>

int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", array + i);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        // int left = 0, right = 0;
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (array[j] >= a && array[j] <= b) {
                count ++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}