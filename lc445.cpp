#include <bits/stdc++.h>
using namespace std;
#define mainTest main

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution{
public://assuming not reversing the linnked list
    ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
        stack<int> stk1,stk2;
        while(l1){
            stk1.emplace(l1->val);
            l1=l1->next;
        }
        while(l2){
            stk2.emplace(l2->val);
            l2=l2->next;
        }
        ListNode* head= nullptr;
        ListNode* cur=head;
        int carry=0;
        while(!stk1.empty() || !stk2.empty()|| carry){
            int sum=carry;
            if(!stk1.empty()){
                sum+=stk1.top();
                stk1.pop();
            }
            if(!stk2.empty()){
                sum+=stk2.top();
                stk2.pop();
            }
            carry=sum/10;
            sum%=10;
            head=new ListNode(sum);
            head->next=cur;
            cur=head;
        }
        return head;
    }
};

// ------------------ Helper functions ------------------
ListNode* buildList(const vector<int>& v) {
    if (v.empty()) return nullptr;
    ListNode* head = new ListNode(v[0]);
    ListNode* cur = head;
    for (int i = 1; i < v.size(); i++) {
        cur->next = new ListNode(v[i]);
        cur = cur->next;
    }
    return head;
}

void printList(ListNode* head) {
    cout << "[";
    while (head) {
        cout << head->val;
        if (head->next) cout << ",";
        head = head->next;
    }
    cout << "]" << endl;
}

// ------------------ mainTest ------------------
int mainTest() {
    Solution sol;

    // Example 1
    vector<int> A1 = {7,2,4,3};
    vector<int> B1 = {5,6,4};
    ListNode* l1 = buildList(A1);
    ListNode* l2 = buildList(B1);
    cout << "Example 1 Output: ";
    printList(sol.addTwoNumbers(l1, l2));  // expected [7,8,0,7]

    // Example 2
    vector<int> A2 = {2,4,3};
    vector<int> B2 = {5,6,4};
    l1 = buildList(A2);
    l2 = buildList(B2);
    cout << "Example 2 Output: ";
    printList(sol.addTwoNumbers(l1, l2));  // expected [8,0,7]

    // Example 3
    vector<int> A3 = {0};
    vector<int> B3 = {0};
    l1 = buildList(A3);
    l2 = buildList(B3);
    cout << "Example 3 Output: ";
    printList(sol.addTwoNumbers(l1, l2));  // expected [0]

    return 0;
}