#include <iostream>
using namespace std;

struct ListNode {
    char val;
    ListNode *pre;
    ListNode *next;
};

struct List {
    ListNode *head = new ListNode;
    ListNode *last = new ListNode;
    List() {
        head->pre = NULL;
        head->next = last;
        head->val = 0;
        last->pre = head;
        last->next = NULL;
        last->val = 0;
    }
};

List list;

ListNode *insertBefore(ListNode *o, char e) {
    ListNode *node = new ListNode;
    node->val = e;
    node->pre = o->pre;
    node->next = o;
    o->pre->next = node;
    o->pre = node;
    return node;
}

ListNode *get(int n) {
    ListNode *result = list.head->next;
    for (int i = 0; i < n; i++) {
        result = result->next;
    }
    return result;
}

void printList() {
    if (list.head->next == list.last) {
        cout << "-" << endl;
        return;
    }
    ListNode *tmp = list.head->next;
    string a;
    while (tmp != list.last) {
        // cout << tmp->val;
        a.push_back(tmp->val);
        tmp = tmp->next;
    }
    printf("%s\n", a.c_str());
}

void resolve3(ListNode *tmp) {
    if (tmp == list.head || tmp == list.last)
        return;
    int val = tmp->val;
    ListNode *pre = tmp->pre;
    ListNode *next = tmp->next;
    int count = 1;
    while (pre != list.head && pre->val == val) {
        count++;
        pre = pre->pre;
    }
    while (next != list.last && next->val == val) {
        count++;
        next = next->next;
    }
    if (count >= 3) {
        ListNode *start = pre->next;
        pre->next = next;
        next->pre = pre;
        while (start != next) {
            ListNode *needdelete = start;
            start = start->next;
            // delete needdelete;
        }
        resolve3(pre);
    }
}

int main() {
    string a;
    getline(cin, a);
    if (a != "-")
        for (int i = 0; i < a.length(); i++) {
            insertBefore(list.last, a[i]);
        }
    int n, index;
    char element;
    scanf("%d", &n);
    ListNode *tmp;
    while (n-- > 0) {
        // cin >> index;
        // cin >> element;
        scanf("%d %c", &index, &element);
        resolve3(insertBefore(get(index), element));
        printList();
    }
    return 0;
}