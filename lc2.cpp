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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *r1=l1,*r2=l2,*prevR2;
        int carry=0;
        while(r1||r2){
            if(r1== nullptr) r2->val+=carry;
            else if(r2== nullptr){
                r2=new ListNode(r1->val+carry,r1->next);
                prevR2->next=r2;
                r1= nullptr;
            }
            else r2->val+=r1->val+carry;
            carry=r2->val/10;
            r2->val%=10;
            if(r1) r1=r1->next;
            prevR2=r2;
            r2=r2->next;
        }
        if(carry) prevR2->next=new ListNode(carry);
        return l2;
    }
};

// Helper function to build the list from the given vector of values
ListNode* buildList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int num : nums) {
        tail->next = new ListNode(num);
        tail = tail->next;
    }
    return dummy.next;
}

// Helper function to convert linked list back to vector for verification
vector<int> listToVector(ListNode* node) {
    vector<int> result;
    while (node) {
        result.push_back(node->val);
        node = node->next;
    }
    return result;
}

int mainTest() {
    // Local function for testing conditions.
    auto test = [](const vector<int>& obtained, const vector<int>& expected, int testNum, const vector<int>& l1_vals, const vector<int>& l2_vals) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        bool isPass = obtained == expected;
        cout << (isPass ? GREEN + "PASS: Test Case " + to_string(testNum) : RED + "FAIL: Test Case " + to_string(testNum)) << RESET;
        if (!isPass) {
            cout << "\n    - l1: [";
            for (const auto& val : l1_vals) cout << val << " ";
            cout << "], l2: [";
            for (const auto& val : l2_vals) cout << val << " ";
            cout << "]\n    Expected: [";
            for (const auto& val : expected) cout << val << " ";
            cout << "], Obtained: [";
            for (const auto& val : obtained) cout << val << " ";
            cout << "]" << RESET;
        }
        cout << endl;
    };


    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> l1;
        vector<int> l2;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{2, 4, 3}, {5, 6, 4}, {7, 0, 8}},           // Test case 1
            {{0}, {0}, {0}},                            // Test case 2
            {{9,9,9,9,9,9,9}, {9,9,9,9}, {8,9,9,9,0,0,0,1}}  // Test case 3
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        const auto& tc = testCases[i];
        ListNode* l1 = buildList(tc.l1);
        ListNode* l2 = buildList(tc.l2);
        ListNode* resultNode = solution.addTwoNumbers(l1, l2);
        vector<int> result = listToVector(resultNode);
        test(result, tc.expected, i + 1, tc.l1, tc.l2);
    }

    return 0;
}
