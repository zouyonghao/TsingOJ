#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

const int N = 1005;

/* 请在这里定义你需要的全局变量 */
typedef long long ll;
typedef pair<int, int> pii;

const ll mo1 = 1e9 + 7; //模数最好都是取质数
const ll mo2 = 1e9 + 9;
const ll pw = 233; //base

ll h1[2][N][N], h2[2][N][N], bb[2][N][N];
// 为了减少复制开销，我们直接读入信息到全局变量中
// a, b：题目所述数组，a的大小为(n+1)*(m+1)，b的大小为(p+1)*(q+1)，下标均从1开始有意义（下标0无意义，你可以直接无视）
// n, m, p, q：题中所述
int a[N][N], b[N][N], n, m, p, q;

// 求出a中有哪些位置出现了b
// 返回值：一个pair<int, int>的数组，包含所有出现的位置
vector<pii> getAnswer()
{
    /* 请在这里设计你的算法 */
    ll p1 = 1, p2 = 1;
    for (int i = 1; i <= q; ++i)
    {
        p1 = p1 * pw % mo1;
        p2 = p2 * pw % mo2;
    }

    p1 = (mo1 - p1) % mo1;
    p2 = (mo2 - p2) % mo2;

    for (int i = 1; i <= n; ++i)
    {
        ll t1 = 0, t2 = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (j < q)
            {
                t1 = (t1 * pw + a[i][j]) % mo1;
                t2 = (t2 * pw + a[i][j]) % mo2;
            }
            else
            {
                t1 = h1[0][i][j] = (t1 * pw + a[i][j] + p1 * a[i][j - q]) % mo1;
                t2 = h2[0][i][j] = (t2 * pw + a[i][j] + p2 * a[i][j - q]) % mo2;
            }
        }
    }

    p1 = 1, p2 = 1;
    for (int i = 1; i <= p; ++i)
    {
        p1 = p1 * pw % mo1;
        p2 = p2 * pw % mo2;
    }

    p1 = (mo1 - p1) % mo1;
    p2 = (mo2 - p2) % mo2;
    //h1[0]数组计算纵向hash值,存储为h1[1],与上方类似
    for (int j = 1; j <= m; ++j)
    {
        ll t1 = 0, t2 = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (i < p)
            {
                t1 = (t1 * pw + h1[0][i][j]) % mo1;
                t2 = (t2 * pw + h2[0][i][j]) % mo2;
            }
            else
            {
                t1 = h1[1][i][j] = (t1 * pw + h1[0][i][j] + p1 * h1[0][i - p][j]) % mo1;
                t2 = h2[1][i][j] = (t2 * pw + h2[0][i][j] + p2 * h2[0][i - p][j]) % mo2;
            }
        }
    }

    //计算b数组的横向hash值,存储为bb数组,与上方类似
    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= q; ++j)
        {
            bb[0][i][j] = (bb[0][i][j - 1] * pw + b[i][j]) % mo1;
            bb[1][i][j] = (bb[1][i][j - 1] * pw + b[i][j]) % mo2;
        }

    //用bb数组的最后一列来计算整个b数组的hash值,存储为p1
    p1 = p2 = 0;
    for (int i = 1; i <= p; ++i)
    {
        p1 = (p1 * pw + bb[0][i][q]) % mo1;
        p2 = (p2 * pw + bb[1][i][q]) % mo2;
    }

    //若值匹配,说明匹配到了相同的矩形(右下角),题中要求输出左上角,故得到的坐标是(i-p+1,j-p+1)
    vector<pii> ans;
    for (int i = p; i <= n; ++i)
        for (int j = q; j <= m; ++j)
            if (h1[1][i][j] == p1 && h2[1][i][j] == p2)
                ans.push_back(pii(i - p + 1, j - q + 1));
    return ans;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &p, &q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= p; ++i)
        for (int j = 1; j <= q; ++j)
            scanf("%d", &b[i][j]);
    vector<pair<int, int>> ans = getAnswer();
    for (int i = 0; i < int(ans.size()); ++i)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}