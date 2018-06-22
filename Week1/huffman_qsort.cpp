// 过了5个用例，还有几个超时
// 输入格式
// 第一行一个整数 n，表示单词种数。
// 第 2 行到第 n+1 行，第 i+1 行包含一个正整数 w[i]，表示第 i 种单词的出现次数。

// 输出格式
// 输出一行一个整数，表示整篇文章重编码后的最短长度。

// 提示
// [我们希望越长的串出现次数越少，那么贪心地考虑，让出现次数少的串更长。]
// [于是我们先区分出出现次数最少的 2 个串，在它们的开头分别添加 0 和 1。]
// [接着，由于它们已经被区分（想一想，为什么？），所以我们可以把它们看作是**一个**单词，且其出现次数为它们的和，然后继续上面的“添数”和“合并”操作。]
// [这样，我们不停地“合并单词”，直到只剩 1 个单词，即可结束。]
// [可以证明这是最优的。]
// [朴素的实现是 O(n^2) 的，可以用二叉堆或__std::priority_queue__将其优化至 O(nlogn)。]

#include <cstdio>
#include <cstdlib>

class node {
private:
    long n;
    node * left;
    node * right;
public:
    node(long _n = -1, node * _left = NULL, node * _right = NULL)
            :n(_n), left(_left), right(_right) { }

    friend node * mergeTwoNode(node *, node *);

    long getValue() {
        return n;
    }

    node * getLeft() {
        return left;
    }
    node * getRight() {
        return right;
    }
};


void count(node * node, long & sum, int depth) {
    if (node->getLeft() == NULL && node -> getRight() == NULL) {
        if (depth == 0) {
            sum = node->getValue();
            return;
        }
        sum += depth * node->getValue();
    } else {
        count(node->getLeft(), sum, depth + 1);
        count(node->getRight(), sum, depth + 1);
    }
}

node * mergeTwoNode(node * left, node * right) {
    return new node(left->n + right->n, left, right);
}

// void insertAndSort(node ** array, node * tmpNode, long size) {
//     long i = 0;
//     for (; i < size; i++) {
//         if (tmpNode->getValue() <= array[i]->getValue()) {
//             // tmp should insert here
//             for (long j = size; j > i; j--) {
//                 array[j] = array[j-1];
//             }
//             array[i] = tmpNode;
//             return;
//         }
//     }
//     array[i] = tmpNode;
// }

int compare(const void * a, const void * b) {
    // printf("%ld\n", (*((node **) a))->getValue());
    // printf("%ld\n", (*((node **) b))->getValue());
    long arg1 = (*((node **) a))->getValue();
    long arg2 = (*((node **) b))->getValue();
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void pop2AndInsert(node ** array, long n) {
    node * min1 = array[0];
    node * min2 = array[1];
    node * result = mergeTwoNode(min1, min2);
    // forward move 2
    array[0] = result;
    array[1] = array[n-1];
    qsort(array, n - 2, sizeof(node *), compare);
}

int main() {
    long n;
    scanf("%ld", &n);
    node ** array = new node * [n];
    long tmp;
    for (long i = 0; i < n; i++) {
        scanf("%ld", &tmp);
        node * tmpNode = new node(tmp);
        array[i] = tmpNode;
    }

    qsort(array, n, sizeof(node *), compare);

    // for (int i = 0; i < n; i++) {
    //     printf("%ld ", array[i]->getValue());
    // }

    for (; n > 1; n--) {
        pop2AndInsert(array, n);
    }
    long result = 0;
    count(array[0], result, 0);
    printf("%ld\n", result);

    return 0;
}