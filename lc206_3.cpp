#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Assuming ListNode is defined as provided in the problem statement
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head== nullptr) return head;
        ListNode* cur=head;
        ListNode* dumhead= new ListNode(0);
        while(cur!= nullptr){
            ListNode* nextNode=cur->next;
            cur->next=dumhead->next;
            dumhead->next=cur;
            cur=nextNode;
        }
        return dumhead->next;
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

    // Array of test cases
    struct TestCase {
        vector<int> input;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1, 3, 5, 7, 9}, {9, 7, 5, 3, 1}},  // Test case 1
            {{2, 4, 6, 8, 10}, {10, 8, 6, 4, 2}}, // Test case 2
            {{}, {}},                            // Test case 3
            // Add more test cases here
    };

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

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list = vectorToList(testCases[i].input);
        ListNode* reversedList = solution.reverseList(list);
        vector<int> result = listToVector(reversedList);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
