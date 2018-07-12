#include <stdio.h>

struct TreeNode {
    int data;
    TreeNode *lc;
    TreeNode *rc;
    TreeNode() {
        data = 0;
        lc = NULL;
        rc = NULL;
    }
};

int trimBST(TreeNode *root, int a, int b) {
    if (NULL == root)
        return 0;
    if (root->data < a) {
        return trimBST(root->rc, a, b);
    } else if (root->data > b) {
        return trimBST(root->lc, a, b);
    } else {
        return 1 + trimBST(root->lc, a, b) + trimBST(root->rc, a, b);
    }
}

void inOrder(TreeNode *root) {
    if (NULL == root)
        return;
    inOrder(root->lc);
    printf("%d ", root->data);
    inOrder(root->rc);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    TreeNode *root = NULL;
    for (int i = 0; i < n; i++) {
        TreeNode *t = new TreeNode;
        int data;
        scanf("%d", &data);
        t->data = data;
        if (root == NULL) {
            root = t;
        } else {
            TreeNode * tmp = root;
            while (tmp != NULL) {
                if (tmp->data < data) {
                    if (tmp->rc != NULL) {
                        tmp = tmp->rc;
                    } else {
                        tmp->rc = t;
                        break;
                    }
                } else {
                    if (tmp->lc != NULL) {
                        tmp = tmp->lc;
                    } else {
                        tmp->lc = t;
                        break;
                    }
                }
            }
        }
    }

    // inOrder(root);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int count = trimBST(root, a, b);
        printf("%d\n", count);
    }

    return 0;
}