#include<bits/stdc++.h>
using namespace std;
#define mainTest main

struct ListNode{
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr){};
    ListNode(int v,ListNode* nxt):val(v),next(nxt){};
    ListNode(int v):val(v),next(nullptr){};
};
class Solution{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists){
        //use minHeap instead of keep searchig for min
        auto cmp=[](ListNode* l1,ListNode* l2){
            //return true making l2 pop first;
            return l1->val>l2->val;
        };
        priority_queue<ListNode*,vector<ListNode*>,decltype(cmp)> minHeap;
        for(int i=0;i<lists.size();i++) if(lists[i]) minHeap.push(lists[i]);
        ListNode dumhead(0);
        ListNode* tail=&dumhead;

        while(!minHeap.empty()){
            ListNode* node=minHeap.top();
            minHeap.pop();
            tail->next=node;
            tail=tail->next;
            if(node->next){
                node=node->next;
                minHeap.push(node);
            }
        }
        return dumhead.next;
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
