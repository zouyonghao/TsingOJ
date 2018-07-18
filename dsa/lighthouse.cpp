// wrong!!

#include <iostream>
using namespace std;

struct LightHouse {
    long X;
    long Y;
};

LightHouse houses[4000000];
LightHouse tmp[4000000];
long n;
long count = 0;

void mergeSort(long start, long end) {
    long length = end - start + 1;
    if (length <= 1)
        return;
    else if (length == 2) {
        if (houses[start].X < houses[end].Y &&
            houses[start].X < houses[end].Y) {
            count++;
        } else {
            swap(houses[start].X, houses[end].X);
            swap(houses[start].Y, houses[end].Y);
        }
        return;
    }
    mergeSort(start, length / 2 - 1);
    mergeSort(length / 2, end);
    long i = 0, left = start, right = length / 2;
    while (left <= length / 2 - 1 && right <= end) {
        if (houses[left].X < houses[right].X &&
            houses[left].Y < houses[right].Y) {
            count++;
            tmp[i++] = houses[left++];
        } else {
            tmp[i++] = houses[right++];
        }
    }
    while (left <= length / 2 - 1) {
        tmp[i++] = houses[left++];
    }
    while (right <= end) {
        tmp[i++] = houses[right++];
        // count += (left - start);
    }
    for (i = start; i <= end; i++) {
        houses[i] = tmp[i];
    }
}

int main() {
    scanf("%ld", &n);
    long x, y;
    for (long i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        houses[i].X = x;
        houses[i].Y = y;
    }
    mergeSort(0, n - 1);
    printf("%d\n", count);
}