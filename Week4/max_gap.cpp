#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

typedef unsigned int u32;

u32 nextInt(u32 x)
{
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

void initData(u32 *a, int n, int k, u32 seed)
{
    for (int i = 0; i < n; ++i)
    {
        seed = nextInt(seed);
        a[i] = seed >> (32 - k);
    }
}

/* 请在这里定义你需要的全局变量 */

const int N = 67108864;

u32 a[N + 1];
u32 l[N + 1], r[N + 1];

// 这是求解答案的函数，你需要对全局变量中的 a 数组求解 maxGap 问题
// n, k：意义与题目描述相符
// 返回值：即为答案（maxGap）
u32 maxGap(int n, int k)
{
    const int m = 1 << 26;
    memset(l, -1, sizeof(int) * m);
    memset(r, -1, sizeof(int) * m);

    const int _k = max(k - 26, 0);
    for (int i = 0; i < n; ++i)
    {
        u32 b1 = a[i] >> _k;
        if (l[b1] == -1)
            l[b1] = r[b1] = a[i];
        else if (a[i] < l[b1])
            l[b1] = a[i];
        else if (a[i] > r[b1])
            r[b1] = a[i];
    }
    //统计答案
    u32 last = a[0];
    u32 ans = 0;
    for (int i = 0; i < m; ++i)
        if (l[i] != -1)
        {
            if (last > l[i])
                last = l[i];
            if (l[i] - last > ans)
                ans = l[i] - last; //
            last = r[i];
        }
    return ans;
}

// ================= 代码实现结束 =================

int main()
{
    int n, k;
    u32 seed;

    scanf("%d%d%u", &n, &k, &seed);
    initData(a, n, k, seed);

    u32 ans = maxGap(n, k);

    printf("%u\n", ans);
    return 0;
}