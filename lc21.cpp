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
private:
    ListNode* min(ListNode *list1,ListNode *list2){
        if(list1== nullptr && list2== nullptr) return nullptr;
        else if(list1== nullptr) return list2;
        else if(list2== nullptr) return list1;
        else if(list1->val<list2->val) return list1;
        return list2;

    }
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1) return list2;
        else if(!list2) return list1;
        ListNode *st=min(list1,list2),*cur=st,*nxNode1=list1,*nxNode2=list2;
        while(cur){
            if(cur==nxNode1) nxNode1=cur->next;
            else nxNode2=cur->next;
            cur->next=min(nxNode1,nxNode2);
            cur=cur->next;
        }

        return st;
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
        vector<int> list1;
        vector<int> list2;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}}, // Original test case 1
            {{}, {}, {}},                              // Original test case 2
            {{}, {0}, {0}},                            // Original test case 3
            {{1, 3, 5, 7, 9}, {2, 4, 6, 8}, {1, 2, 3, 4, 5, 6, 7, 8, 9}}, // New test case 1
            {{-3, 1, 4}, {-2, 2, 3}, {-3, -2, 1, 2, 3, 4}},              // New test case 2
            {{2, 4, 6, 8}, {1, 3, 5, 7}, {1, 2, 3, 4, 5, 6, 7, 8}},      // New test case 3
            {{5}, {10}, {5, 10}},                                        // New test case 4
            {{-10, -5, 0, 5}, {-6, -2, 1, 3}, {-10, -6, -5, -2, 0, 1, 3, 5}}, // New test case 5
            {{10, 20, 30}, {5, 15, 25}, {5, 10, 15, 20, 25, 30}},        // New test case 6
            {{15}, {0, 30, 45}, {0, 15, 30, 45}},                        // New test case 7
            {{}, {-1, 2, 3}, {-1, 2, 3}},                                // New test case 8
            {{-1, 0, 1}, {-2, 2}, {-2, -1, 0, 1, 2}},                    // New test case 9
            {{0}, {1, 2, 3}, {0, 1, 2, 3}},                               // New test case 10
            {{1,2,3}, {8,9,10,11,12,13}, {1,2,3,8,9,10,11,12,13}}                               // New test case 10
    };


    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list1 = vectorToList(testCases[i].list1);
        ListNode* list2 = vectorToList(testCases[i].list2);
        ListNode* mergedList = solution.mergeTwoLists(list1, list2);
        vector<int> result = listToVector(mergedList);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
    /**
    This mainTest() function:

    - Defines a test lambda function to compare the obtained and expected values. If the test fails, the expected and obtained values are highlighted in red.
    - Initializes a Solution object to test the mergeTwoLists method.
    - Includes utility functions to convert between vectors and linked lists, facilitating easy setup of inputs and verification of outputs.
    - Iterates through an array of test cases to verify the correctness of the mergeTwoLists method.

    After you implement the mergeTwoLists method, compile and run this program to test its functionality. If a test fails, the function will clearly indicate which test case failed and highlight the discrepancies, helping you identify where your method might need adjustments.
    **/
}
