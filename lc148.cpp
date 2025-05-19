#include <bits/stdc++.h>
#define testMain main
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode *next): val(x), next(next) {}
};

class Solution {
private:
    pair<ListNode*,ListNode*> divide(ListNode* head){//return <head,mid>
        if(!head) return {nullptr,nullptr};
        //using fast slow ptr
        ListNode* fast=head,*slow=head;
        ListNode* mid_prev;
        while(fast && fast->next){
            fast=fast->next->next;
            mid_prev=slow;
            slow=slow->next;
        }
        //cut the list
        mid_prev->next= nullptr;//slow is the head of the second half
        return {head,slow};
    }
    ListNode* merge(ListNode* l1,ListNode* l2){
        if(!l1) return l2;
        else if(!l2) return l1;
        ListNode dummyhead(0);
        ListNode* prev=&dummyhead;
        while (l1 && l2){
            if(l1->val<l2->val){
                prev->next=l1;
                l1=l1->next;
            }
            else {
                prev->next=l2;
                l2=l2->next;
            }
            prev=prev->next;
        }
        prev->next=l1?l1:l2;
        return dummyhead.next;
    }
public:
    ListNode* sortList(ListNode* head) {
        // using merge sort so that time: nlogn, space: logn(recursion)
        if(!head || !head->next) return head;//base case
        auto [l1,l2]= divide(head);
        return merge(sortList(l1), sortList(l2));
    }
};

// Helper to build a linked list from a vector
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper to convert a linked list to a vector
vector<int> listToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, const vector<int>& input, const vector<int>& expected) {
    ListNode* head = buildList(input);
    Solution sol;
    ListNode* sorted = sol.sortList(head);
    vector<int> result = listToVector(sorted);

    const string GREEN = "\033[32m", RED = "\033[31m", RESET = "\033[0m";
    if (result == expected) {
        cout << GREEN << "Test Case " << testNum << " Passed: ";
        printVector(result);
        cout << RESET << "\n";
    } else {
        cout << RED << "Test Case " << testNum << " Failed: got ";
        printVector(result);
        cout << ", expected ";
        printVector(expected);
        cout << RESET << "\n";
    }
}

int testMain() {
    // Example 1:
    // Input: [4,2,1,3] -> Output: [1,2,3,4]
    runTest(1, {4,2,1,3}, {1,2,3,4});

    // Example 2:
    // Input: [-1,5,3,4,0] -> Output: [-1,0,3,4,5]
    runTest(2, {-1,5,3,4,0}, {-1,0,3,4,5});

    // Example 3:
    // Input: [] -> Output: []
    runTest(3, {}, {});

    return 0;
}