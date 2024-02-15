#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Assuming ListNode is defined as provided in the problem statement
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode dummy=ListNode(-1);
        dummy.next=head;
        ListNode *f=head;
        ListNode *s=&dummy;
        while(f->next && f->next->next && f!=s){
            f=f->next->next;
            s=s->next;
        }
        return f==s;
    }
};

// Helper function to build the list and introduce a cycle
ListNode* buildCyclicList(const vector<int>& nums, int pos) {
    if(nums.empty()) return nullptr;

    ListNode dummy(0);
    ListNode* tail = &dummy;
    vector<ListNode*> createdNodes;

    for (int num : nums) {
        tail->next = new ListNode(num);
        tail = tail->next;
        createdNodes.push_back(tail);
    }

    if (pos != -1 && pos < nums.size()) {
        tail->next = createdNodes[pos]; // Creating the cycle
    }

    return dummy.next;
}

int mainTest() {
    // Local function for testing conditions.
    auto test = [](bool obtained, bool expected, int testNum) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        cout << (obtained == expected ? GREEN + "PASS: Test Case " + to_string(testNum) : RED + "FAIL: Test Case " + to_string(testNum)) << RESET << endl;
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> list;
        int pos; // The position where the tail should connect to form a cycle
        bool expected;
    };

    vector<TestCase> testCases = {
            {{3, 2, 0, -4}, 1, true},  // Test case 1
            {{1, 2}, 0, true},        // Test case 2
            {{1}, -1, false}          // Test case 3
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list = buildCyclicList(testCases[i].list, testCases[i].pos);
        bool result = solution.hasCycle(list);
        test(result, testCases[i].expected, i + 1);
    }

    return 0;
}
