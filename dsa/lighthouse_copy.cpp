#include <stdio.h>
#include <stdlib.h>

#define MAXN 200002

typedef struct P {
    long x;
    long y;
} Point;

Point p[MAXN];
long A[MAXN];
long cunt = 0;
long L[MAXN], R[MAXN];
const long M = 999999999;

//按照 x 的值从小到大将结构体排序
int cmp(const void *a, const void *b) {
    return (*(Point *)a).x > (*(Point *)b).x ? 1 : -1;
}

void Merge(long Left, long Middle, long Right) {
    long n1 = Middle - Left + 1;
    long n2 = Right - Middle;

    long i, k;
    for (i = 1; i <= n1; i++)
        L[i] = A[Left + i - 1];
    for (i = 1; i <= n2; i++)
        R[i] = A[Middle + i];

    L[n1 + 1] = M;
    R[n2 + 1] = M;

    i = 1;
    long j = 1;
    for (k = Left; k <= Right; k++) {
        if (L[i] <= R[j])
            A[k] = L[i++];

        else {
            A[k] = R[j++];
            cunt += n1 - i + 1; // cunt为全局变量
        }
    }
}

void Merge_sort(long Left, long Right) {
    long Middle;
    if (Left < Right) {
        Middle = (Left + Right) / 2;
        Merge_sort(Left, Middle);      // 二分分解左部分
        Merge_sort(Middle + 1, Right); // 二分分解有部分
        Merge(Left, Middle, Right);    //合并两部分
    }
}

int main() {
    long n;
    scanf("%d", &n);

    long i;
    for (i = 0; i < n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);

    //按照 x 坐标进行排序
    qsort(p, n, sizeof(p[0]), cmp);

    for (i = 0; i < n; i++)
        A[i + 1] = p[i].y;

    Merge_sort(1, n);

    long tmp = (n * (n - 1)) >> 1;
    printf("%ld\n", tmp - cunt);

    return 0;
}