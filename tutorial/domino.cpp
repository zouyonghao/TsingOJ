#include "stdio.h"

int main() {
    int n;
    scanf("%d", &n);
    if (n < 3) {
        printf("%d", 0);
        return 0;
    }
    long long sum = 0L;
    int **allCombinations = new int *[n + 1];
    allCombinations[2] = new int[4];
    allCombinations[2][0] = 0;
    allCombinations[2][1] = 0;
    allCombinations[2][2] = 0;
    allCombinations[2][3] = 0;
    for (int i = 3; i <= n; i++) {
        allCombinations[i] = new int[1 << i];
        for (int j = 0; j < (1 << (i - 1)); j++) {
            int prev = allCombinations[i - 1][j];
            int index1 = (j << 1) + 0;
            int index2 = (j << 1) + 1;
            if (prev == 0) {
                int left = j % 4;
                if (left == 0) {
                    allCombinations[i][index1] = 1;
                    allCombinations[i][index2] = 0;
                } else if (left == 3) {
                    allCombinations[i][index1] = 0;
                    allCombinations[i][index2] = 1;
                } else {
                    allCombinations[i][index1] = 0;
                    allCombinations[i][index2] = 0;
                }
            } else {
                allCombinations[i][index1] = 1;
                allCombinations[i][index2] = 1;
            }
        }
        delete[] allCombinations[i - 1];
    }
    for (int i = 0; i < 1 << n; i++) {
        if (allCombinations[n][i] == 1) {
            sum++;
        }
    }
    printf("%d", sum);
    return 0;
}
