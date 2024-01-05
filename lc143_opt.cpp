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
    void reverseList(ListNode **head){
        ListNode *orgPrev= nullptr,*orgNext= nullptr,*cur=*head;
        while(cur!= nullptr){
            orgNext=cur->next;
            cur->next=orgPrev;
            orgPrev=cur;
            cur=orgNext;
        }
        *head=orgPrev;
    }
    void mergeList(ListNode **head1, ListNode **head2){//go to head1
        ListNode *orgNext1,*orgNext2;
        ListNode *cur1=*head1,*cur2=*head2;
        while(cur1!= nullptr && cur2!= nullptr){
            //確實只要執行一半就好，因為沒執行的會remain as it is
            orgNext1=cur1->next;
            orgNext2=cur2->next;
            cur1->next=cur2;
            cur2->next=orgNext1;
            cur1=orgNext1;
            cur2=orgNext2;
        }
    }
public:
    void reorderList(ListNode* head) {
        if(head== nullptr || head->next== nullptr) return;
        ListNode *slow=head;
        ListNode *fast=head;
        while (fast!= nullptr && fast->next!= nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }

        ListNode *secondHalf=slow->next;
        slow->next= nullptr;//fast=nullptr or fast->next=nullptr & slow=half
        reverseList(&secondHalf);
        mergeList(&head,&secondHalf);
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
