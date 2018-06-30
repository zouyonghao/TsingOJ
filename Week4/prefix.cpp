#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

const int M = 505, L = 1000005;

int c[L][26], sz[L], cnt;

void add(char *s)
{
    int x = 0;
    for (; *s; ++s)
    {
        int y = *s - 'a';
        if (!c[x][y])
            c[x][y] = ++cnt;
        x = c[x][y];
        ++sz[x];
    }
}
int walk(char *s)
{
    int x = 0;
    for (; *s; ++s)
    {
        int y = *s - 'a';
        if (!c[x][y])
            return 0;
        x = c[x][y];
    }
    return x;
}

// ================= 代码实现结束 =================

char s[M];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (; n--;)
    {
        scanf("%s", s);
        add(s);
    }

    for (; m--;)
    {
        scanf("%s", s);
        printf("%d\n", sz[walk(s)]);
    }
    return 0;
}