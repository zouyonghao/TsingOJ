#include <stdio.h>
// #include <stdlib.h>
/*
const int SZ = 1 << 20;  //提升IO buff
struct fastio{
char inbuf[SZ];
char outbuf[SZ];
fastio(){
setvbuf(stdin, inbuf, _IOFBF, SZ);
setvbuf(stdout, outbuf, _IOFBF, SZ);
}
}io;
*/

#define MAXN 4000010
struct Point // 坐标结构体
{
    long x;
    long y;
} points[MAXN];

long count;
long src[MAXN];
long des[MAXN];

// 快排，对x排序
void qsort(Point ps[], int l, int r) {
    if (l < r) {
        int i = l, j = r;
        Point tmp;
        tmp.x = ps[i].x;
        tmp.y = ps[i].y;
        int key = ps[i].x;

        while (i < j) {
            while (i < j && key < ps[j].x)
                --j;
            ps[i].x = ps[j].x;
            ps[i].y = ps[j].y;
            while (i < j && ps[i].x < key)
                ++i;
            ps[j].x = ps[i].x;
            ps[j].y = ps[i].y;
        }

        ps[i].x = tmp.x;
        ps[i].y = tmp.y;

        qsort(ps, l, i - 1);
        qsort(ps, i + 1, r);
    }
}
// 归并，对y进行“顺序对”统计
void merge(long *src, long *des, int start, int mid, int end) {
    int i = start, j = mid + 1;
    int k = start;

    while (i != mid + 1 && j != end + 1) {
        if (src[i] < src[j]) {
            des[k++] = src[i++];
            count += end - j + 1; // 统计“顺序”个数
        } else
            des[k++] = src[j++];
    }
    while (i != mid + 1)
        des[k++] = src[i++];
    while (j != end + 1)
        des[k++] = src[j++];
    for (i = start; i != end + 1; ++i)
        src[i] = des[i];
}

void mergeSort(long *src, long *des, int start, int end) {
    int mid;
    if (start < end) {
        mid = (start + end) >> 1;
        mergeSort(src, des, start, mid);
        mergeSort(src, des, mid + 1, end);
        merge(src, des, start, mid, end);
    }
}
/*
int cmp(const void *a, const void *b)
{<span style="white-space:pre">	</span>// 定义排序规则，这里为从小到大
        return (*(Point *)a).x > (*(Point *)b).x ? 1 : -1;
}
*/
int main() {

    int n;
    int i;
    scanf("%d", &n);

    for (i = 0; i < n; ++i)
        scanf("%ld %ld", &points[i].x, &points[i].y);

    //  qsort(points, n, sizeof(points[0]), cmp); //
    //  用系统的快排，最后一个实例不能通过

    qsort(points, 0, n - 1); // 用自己写的快排，最后一个实例可通过
    for (i = 0; i < n; ++i)
        src[i] = points[i].y;

    count = 0;
    mergeSort(src, des, 0, n - 1);

    printf("%ld\n", count);

    return 0;
}