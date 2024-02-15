#include <iostream>
#include <vector>
using namespace std;
#define mainTest main

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    int getDecimalValue(ListNode* head) {
        ListNode *cur=head;
        int res=0;
        while(cur){
            res=2*res+cur->val;
            cur=cur->next;
        }
        return res;
    }
};

ListNode* createLinkedList(const vector<int>& values) {
    ListNode *head = nullptr, *tail = nullptr;
    for (int val : values) {
        ListNode* newNode = new ListNode(val);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void printTestResult(int testNum, int expected, int actual) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "Passed\n";
    } else {
        cout << "Failed. Expected: " << expected << ", Actual: " << actual << endl;
    }
}

int mainTest() {
    vector<vector<int>> testCases = {{1,0,1}, {0}, {1,1,1,1,1}};
    vector<int> expectedResults = {5, 0, 31};
    int testNum = 0;

    for (size_t i = 0; i < testCases.size(); ++i) {
        ListNode* head = createLinkedList(testCases[i]);
        Solution solution;
        int actualResult = solution.getDecimalValue(head);
        printTestResult(++testNum, expectedResults[i], actualResult);
        deleteLinkedList(head);
    }

    return 0;
}
