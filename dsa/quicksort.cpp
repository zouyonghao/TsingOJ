#include <stdio.h>

void quicksort(int *array, int l, int r) {
    int left = l;
    int right = r;
    if (r <= l)
        return;
    int p = array[left];
    while (left < right) {
        // 必须先右后左，因为左边已经把p存下来了，因此可以直接覆盖。
        while ((left < right) && p <= array[right]) {
            right--;
        }
        array[left] = array[right];
        while ((left < right) && array[left] <= p) {
            left++;
        }
        array[right] = array[left];
    }
    array[left] = p;
    quicksort(array, l, left - 1);
    quicksort(array, left + 1, r);
}

// int main() {
//     int n;
//     scanf("%d", &n);
//     int * array = new int[n];
//     for (int i = 0; i < n; i++) {
//         scanf("%d", array + i);
//     }
//     quicksort(array, 0, n - 1);
//     for (int i = 0; i < n; i++) {
//         printf("%d ", array[i]);
//     }
//     return 0;

// }