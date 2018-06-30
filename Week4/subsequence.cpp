#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */
const int N = 500005, mo = 23333;

int f[N], p[N], last[26];
int n;
char s[N];

// 求出字符串s有多少不同的子序列
// 返回值：s不同子序列的数量，返回值对mo取模
int getAnswer()
{
    for (int i = 1; i <= n; ++i)
    {
        int a = s[i] - 'a';
        p[i] = last[a];
        last[a] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (p[i])
            f[i] = f[i - 1] + f[i - 1] - f[p[i] - 1] + mo;
        else
            f[i] = f[i - 1] + f[i - 1] + 1;
        f[i] %= mo;
    }
    return f[n];
}

// ================= 代码实现结束 =================

int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    printf("%d\n", getAnswer());
    return 0;
}