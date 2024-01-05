#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Assuming ListNode is defined as provided in the problem statement
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        stack<ListNode*> stk;
        ListNode *cur=head;
        int len=0,offset;
        while (cur!= nullptr){
            ++len;
            cur=cur->next;
        }
        offset=len/2+1;
        cur=head;
        while (--offset>=1) cur=cur->next;
        ListNode *stackSt=cur->next;
        cur->next= nullptr;
        while(stackSt!= nullptr){
            stk.push(stackSt);
            stackSt=stackSt->next;
        }
        cur=head;
        while(cur!= nullptr){
            if(!stk.empty()){
                ListNode *orgNext=cur->next;
                cur->next=stk.top();
                stk.pop();
                cur=cur->next;
                cur->next=orgNext;
            }
            cur=cur->next;
        }
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](const vector<int>& obtained, const vector<int>& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        bool isPass = obtained == expected;
        cout << (isPass ? GREEN + "PASS" : RED + "FAIL") << RESET << ": " << testName;
        if (!isPass) {
            cout << " - Expected: " << RED << "[";
            for (const auto& val : expected) cout << val << " ";
            cout << "]" << RESET << ", Obtained: " << RED << "[";
            for (const auto& val : obtained) cout << val << " ";
            cout << "]" << RESET;
        }
        cout << endl;
    };

    Solution solution;

    // Function to convert vector to linked list for testing
    auto vectorToList = [](const vector<int>& nums) {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        for (int num : nums) {
            if (!head) {
                head = tail = new ListNode(num);
            } else {
                tail->next = new ListNode(num);
                tail = tail->next;
            }
        }
        return head;
    };

    // Function to convert linked list back to vector for verification
    auto listToVector = [](ListNode* node) {
        vector<int> result;
        while (node) {
            result.push_back(node->val);
            node = node->next;
        }
        return result;
    };

    // Array of test cases
    struct TestCase {
        vector<int> input;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1, 2, 3, 4}, {1, 4, 2, 3}},       // Test case 1
            {{1, 2, 3, 4, 5}, {1, 5, 2, 4, 3}},  // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list = vectorToList(testCases[i].input);
        solution.reorderList(list);
        vector<int> result = listToVector(list);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
