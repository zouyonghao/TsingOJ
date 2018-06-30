#include <bits/stdc++.h>
using namespace std;

// ================= 代码实现开始 =================

typedef unsigned int u32;

// 以下代码不需要解释，你只需要知道这是用于生成数据的就行了

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

u32 hashArr(u32 *a, int n)
{
    u32 x = 998244353, ret = 0;
    for (int i = 0; i < n; ++i)
    {
        ret ^= (a[i] + x);
        x = nextInt(x);
    }
    return ret;
}

// 以上代码不需要解释，你只需要知道这是用于生成数据的就行了

/* 请在这里定义你需要的全局变量 */
const int N = 100000000;

// a,输入中给定的数组
// _a:
u32 a[N + 1];  //为了省去传入数据花费的时间,我们直接将你要排序的数组开设成了全局变量
u32 _a[N + 1]; //用于辅助基数排序的临时数组

const int m = 16;     //基数排序中的参数,表示每次排序的二进制位数
const int B = 1 << m; //2的m次幂,表示一次排序中的值域
const int b = B - 1;  //这是一个用于辅助计算的常值,它在二进制下的最低m位均为1

// sum :在基数排序中记录各值出现的次数
int sum[B + 1];

// 这是你的排序函数，你需要将全局变量中的 a 数组进行排序
// n, k：意义与题目描述相符
// 返回值：本函数需不要返回值（你只需要确保 a 被排序即可）
void sorting(int n, int k)
{
    /* 请在这里设计你的算法 */
    // 针对_a的后16位进行基数排序
    memset(sum, 0, sizeof(sum)); //将sum数组清零
    for (int i = 0; i < n; ++i)  //统计待排序二进制各值出现的次数
        ++sum[a[i] & b];         //a[i]&b等价与取出a[i]的对应二进制位
    //接下来需要对sum数组进行操作
    for (int i = 1; i < B; ++i)
        sum[i] += sum[i - 1];
    //求出每个位置每个值的名次
    for (int i = n - 1; i >= 0; --i)
        _a[--sum[a[i] & b]] = a[i];

    //再重复一遍上面的基数排宿,只不过这次是对_a的前16位排序,并存入a中
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < n; ++i)
        ++sum[(_a[i] >> m) & b];
    for (int i = 1; i < B; ++i)
        sum[i] += sum[i - 1];
    for (int i = n - 1; i >= 0; --i)
        a[--sum[(_a[i] >> m) & b]] = _a[i];
}

// ================= 代码实现结束 =================

int main()
{
    int n, k;
    u32 seed;
    scanf("%d%d%u", &n, &k, &seed);
    initData(a, n, k, seed);

    sorting(n, k);

    u32 ans = hashArr(a, n);
    printf("%u\n", ans);
    return 0;
}