#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */
// [low, high]
void mergesort(vector<int> & a, int low, int high) {
    if (low >= high) {
        return;
    }
    int mid = (low + high) / 2;
    mergesort(a, low, mid);
    mergesort(a, mid + 1, high);
    vector<int> sorted;
    int i = low, j = mid + 1;
    while(i <= mid && j <= high) {
        if (a[i] < a[j]) {
            sorted.push_back(a[i++]);
        } else {
            sorted.push_back(a[j++]);
        }
    }
    while (i <= mid) {
        sorted.push_back(a[i++]);
    }
    while (j <= high) {
        sorted.push_back(a[j++]);
    }
    for (int i = low; i <= high; i++) {
        a[i] = sorted[i - low];
    }
}

// 将给定数组a升序排序
// n：数组大小
// a：所给数组，大小为n
// 返回值：排序后的数组
vector<int> getAnswer(int n, vector<int> a) {
    if (n <= 1) {
        return a;
    }
    mergesort(a, 0, n - 1);
    return a;
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    a = getAnswer(n, a);
    for (int i = 0; i < n; ++i)
        printf("%d%c", a[i], " \n"[i == n - 1]);
    return 0;
}
