#include <stdio.h>
// AVL tree
struct TreeNode {
    int data;
    TreeNode *parent;
    TreeNode *lc;
    TreeNode *rc;
    int h;
    TreeNode() {
        data = 0;
        parent = NULL;
        lc = NULL;
        rc = NULL;
    }
};

bool IsLChild(TreeNode *x) {
    if (x->parent == NULL) {
        return false;
    } else {
        return x->parent->lc == x;
    }
}

int height(TreeNode *x) {
    if (x == NULL) {
        return -1;
    }
    return x->h;
}

int stature(TreeNode *x) {
    if (x == NULL) {
        return -1;
    }
    return 1 + (height(x->lc) > height(x->rc) ? height(x->lc) : height(x->rc));
}

bool AVLBalanced(TreeNode *x) {
    int leftHeight = x->lc ? x->lc->h : -1;
    int rightHeight = x->rc ? x->rc->h : -1;
    int balfac = leftHeight - rightHeight;
    return -2 < balfac && balfac < 2;
}

TreeNode *connect34(TreeNode *a, TreeNode *b, TreeNode *c, TreeNode *T0,
                    TreeNode *T1, TreeNode *T2, TreeNode *T3) {
    a->lc = T0;
    if (T0)
        T0->parent = a;
    a->rc = T1;
    if (T1)
        T1->parent = a;
    c->lc = T2;
    if (T2)
        T2->parent = c;
    c->rc = T3;
    if (T3)
        T3->parent = c;
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    b->h = stature(b);
    return b;
}

TreeNode *tallerChild(TreeNode *x) {
    if (stature(x->lc) > stature(x->rc)) {
        return x->lc;
    } else if (stature(x->lc) < stature(x->rc)) {
        return x->rc;
    } else {
        return IsLChild(x) ? x->lc : x->rc;
    }
}

TreeNode *rotateAt(TreeNode *v) {
    TreeNode *p = v->parent;
    TreeNode *g = p->parent;
    if (IsLChild(p)) {
        if (IsLChild(v)) {
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {
        if (!IsLChild(v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

void reblance(TreeNode * &root, TreeNode *x) {
    for (; x != NULL; x = x->parent) {
        if (!AVLBalanced(x)) {
            TreeNode * parent = x->parent;
            TreeNode *&p = x->parent ? ((IsLChild(x) ? x->parent->lc : x->parent->rc)) : x;
            p = rotateAt(tallerChild(tallerChild(x)));
            if (p->parent == NULL) {
                root = p;
            }
            break;
        } else {
            x->h = stature(x);
        }
    }
}

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
            TreeNode *tmp = root;
            while (tmp != NULL) {
                if (tmp->data < data) {
                    if (tmp->rc != NULL) {
                        tmp = tmp->rc;
                    } else {
                        tmp->rc = t;
                        t->parent = tmp;
                        reblance(root, t);
                        // inOrder(root);
                        break;
                    }
                } else {
                    if (tmp->lc != NULL) {
                        tmp = tmp->lc;
                    } else {
                        tmp->lc = t;
                        t->parent = tmp;
                        reblance(root, t);
                        // inOrder(root);
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