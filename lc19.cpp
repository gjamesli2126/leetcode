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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head== nullptr) return nullptr;
        else if(head->next== nullptr && n==1) return nullptr;
        ListNode dummyHead(0);
        dummyHead.next=head;
        ListNode *lead=head;
        ListNode *lag=&dummyHead;//為了要讓lag退一格
        while(n--) lead=lead->next;
        while(lead!= nullptr) {
            lead=lead->next;
            lag=lag->next;
        }
        lag->next=lag->next->next;

        return dummyHead.next;
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
        int n;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1, 2, 3, 4, 5}, 2, {1, 2, 3, 5}},  // Test case 1
            {{1}, 1, {}},                        // Test case 2
            {{1, 2}, 1, {1}}        ,             // Test case 3
            {{1, 2,3}, 3, {2,3}}        ,
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list = vectorToList(testCases[i].input);
        ListNode* modifiedList = solution.removeNthFromEnd(list, testCases[i].n);
        vector<int> result = listToVector(modifiedList);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
