#include <cmath>
#include <iostream>
#include <stdio.h>
using namespace std;

const int N = 5 * 1e5 + 5;
int v[N];

int Position(int low, int high, int e) {
    while (low < high) {
        int mid = (low + high) / 2;
        if (v[mid] > e)
            high = mid;
        else
            low = mid + 1;
    }
    low--;
    return low;
}

void QuickSort(int lo, int hi) {
    if (lo < hi) {
        int i = lo, j = hi, x = v[lo];
        while (i < j) {
            while (i < j && v[j] >= x)
                --j;
            if (i < j)
                v[i++] = v[j];
            while (i < j && v[i] < x)
                ++i;
            if (i < j)
                v[j--] = v[i];
        }
        v[i] = x;
        QuickSort(lo, i - 1);
        QuickSort(i + 1, hi);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    QuickSort(0, n - 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int p1 = Position(0, n, a);
        while (v[p1] == a && p1 >= 0)
            p1--;
        int p2 = Position(0, n, b);
        int count = p2 - p1;
        printf("%d\n", count);
    }
    return 0;
}