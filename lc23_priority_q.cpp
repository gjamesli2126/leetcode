#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define mainTest main

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//space O(k)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp=[&](ListNode* x,ListNode* y){
            return x->val>y->val;//if return true, then y will be popped first-->minheap
        };
        priority_queue<ListNode*,vector<ListNode*>,decltype(cmp)> minheap(cmp);
        //store k ptrs into minheap
        for(ListNode* l:lists) if(l) minheap.push(l);
        //let min node store onto the result;
        ListNode dummhead(0);
        ListNode* node=&dummhead;
        while(!minheap.empty()){
            node->next=minheap.top();
            minheap.pop();
            node=node->next;
            if(node->next) minheap.push(node->next);
        }
        return dummhead.next;
    }
};

// Helper: Create a linked list from a vector of integers.
ListNode* createLinkedList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper: Convert a linked list to a vector of integers.
vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Helper: Free memory allocated for a linked list.
void freeLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Improved test harness.
// Note: Since mergeKLists reuses nodes from the input lists, we only free the merged list
// and then null out the original list pointers to avoid double deletion.
void runTest(int testNum, const vector<vector<int>>& inputLists, const vector<int>& expected) {
    vector<ListNode*> lists;
    for (const auto& vec : inputLists) {
        // If the vector is empty, push a nullptr.
        lists.push_back(vec.empty() ? nullptr : createLinkedList(vec));
    }

    Solution sol;
    ListNode* merged = sol.mergeKLists(lists);
    vector<int> resultVec = linkedListToVector(merged);

    bool pass = (resultVec == expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: ";
        for (int v : expected) {
            cout << v << " ";
        }
        cout << "\nGot: ";
        for (int v : resultVec) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Free the merged list.
    freeLinkedList(merged);

    // Set the original list pointers to nullptr to avoid double free.
    for (auto& node : lists) {
        node = nullptr;
    }
}

int mainTest() {
    runTest(1, {{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6});
    runTest(2, {}, {});
    runTest(3, {{}}, {});
    return 0;
}