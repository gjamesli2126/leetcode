#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int scout=0;
        int exe;
        ListNode dummy(0,head);
        ListNode* node=head;
        while(node){
            node=node->next;
            scout++;
        }
        exe=scout-n;
        node=&dummy;
        while(exe--) node=node->next;
        //at this point, the node is the previous of toBeOmited node
        node->next=node->next?node->next->next: nullptr;
        return dummy.next;
    }
};
// Helper function: Create a linked list from a vector of integers.
ListNode* createLinkedList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper function: Convert a linked list to a vector of integers.
vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Helper function: Free the allocated linked list.
void freeLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> inputList, int n, vector<int> expected) {
    // Create the linked list from inputList
    ListNode* head = createLinkedList(inputList);

    // Call the solution
    Solution sol;
    ListNode* newHead = sol.removeNthFromEnd(head, n);

    // Convert the resulting list to a vector
    vector<int> resultVec = linkedListToVector(newHead);

    // Compare with expected
    bool pass = (resultVec == expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed\033[0m" << endl;
        cout << "Expected: ";
        for (auto v : expected) cout << v << " ";
        cout << "\nGot: ";
        for (auto v : resultVec) cout << v << " ";
        cout << endl;
    }

    // Free the linked list
    freeLinkedList(newHead);
}

int testMain(){
    // Test Case 1:
    // Input: head = [1,2,3,4,5], n = 2
    // Expected Output: [1,2,3,5]
    runTest(1, {1,2,3,4,5}, 2, {1,2,3,5});

    // Test Case 2:
    // Input: head = [1], n = 1
    // Expected Output: []
    runTest(2, {1}, 1, {});

    // Test Case 3:
    // Input: head = [1,2], n = 1
    // Expected Output: [1]
    runTest(3, {1,2}, 1, {1});

    runTest(4, {1,2}, 2, {2});

    return 0;
}//
// Created by Julieanna Li on 2025/4/2.
//
