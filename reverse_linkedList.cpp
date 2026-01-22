#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node* next;
    node(int v) : val(v), next(nullptr) {}
};

void recurrsion(node* cur, node** prev) {
    if (!cur) return;
    node* nxt = cur->next;
    cur->next = *prev;
    *prev = cur;
    recurrsion(nxt, prev);
}

node* reverse(node* head) {
    node* prev = nullptr;
    recurrsion(head, &prev);
    return prev;
}

void printList(node* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Build list: 1 -> 2 -> 3 -> 4
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);

    cout << "Original: ";
    printList(head);

    head = reverse(head);

    cout << "Reversed: ";
    printList(head);

    return 0;
}