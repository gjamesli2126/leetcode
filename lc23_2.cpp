#include<bits/stdc++.h>
using namespace std;
#define mainTest main

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(const vector<ListNode*>& lists) {
        //priorityQueue's cmp return true meaning b will be popped first
        //potential optimization: if lists.size()<4 then use merge2List method to save space
        auto cmp=[](const ListNode* l1,const ListNode* l2){
            return l1->val>l2->val;//b will be popped first if return true
        };
        priority_queue<ListNode*,vector<ListNode*>, decltype(cmp)> minHeap;
        for(auto& list:lists){
            if(list) minHeap.push(list);
        }
        ListNode dummyHead(0);
        ListNode* tail=&dummyHead;
        while(!minHeap.empty()){
            ListNode* node=minHeap.top();
            minHeap.pop();
            tail->next=node;
            tail=tail->next;
            if(node->next) minHeap.push(node->next);
        }
        return dummyHead.next;
    }
};
ListNode* buildList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int num : nums) {
        tail->next = new ListNode(num);
        tail = tail->next;
    }
    return dummy.next;
}

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
    auto test = [](const vector<int>& obtained, const vector<int>& expected, int testNum) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        cout << (obtained == expected ? GREEN + "PASS: Test Case " + to_string(testNum) : RED + "FAIL: Test Case " + to_string(testNum));
        if (obtained != expected) {
            cout << " - Expected: " << RED << "[";
            for (const auto& val : expected) cout << val << " ";
            cout << "]" << RESET << ", Obtained: " << RED << "[";
            for (const auto& val : obtained) cout << val << " ";
            cout << "]" << RESET;
        }
        cout << endl;
    };

    Solution solution;

    vector<vector<vector<int>>> testCases = {
            {{1, 4, 5}, {1, 3, 4}, {2, 6}},  // Test case 1
            {},                             // Test case 2
            {{}}                            // Test case 3
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        vector<ListNode*> lists;
        for (auto &list : testCases[i]) {
            lists.push_back(buildList(list));
        }
        ListNode* resultNode = solution.mergeKLists(lists);
        vector<int> result = listToVector(resultNode);
        vector<int> expected;
        for (auto &list : testCases[i]) {
            expected.insert(expected.end(), list.begin(), list.end());
        }
        sort(expected.begin(), expected.end()); // As the merged list should be sorted
        test(result, expected, i + 1);
    }

    return 0;
}
