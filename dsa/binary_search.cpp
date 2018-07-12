#include "quicksort.cpp"

int binary_search(int * array, int n, int m) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (array[mid] < m) {
            left = mid + 1;
        } else if (array[mid] == m) {
            return mid;
        } else {
            right = mid - 1;
        }
    }
    return -1;
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
//     printf("\n");
//     int m;
//     scanf("%d", &m);
//     int rank = binary_search(array, n, m);
//     printf("%d\n", rank);
//     return 0;
// }