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
private:
    ListNode* minNode(ListNode *n1,ListNode *n2){
        if(!n1 && !n2) return nullptr;
        else if(n1== nullptr) return n2;
        else if(n2== nullptr) return n1;
        if(n1->val < n2->val) return n1;
        else return n2;
    }
    ListNode* merge(ListNode *l1,ListNode *l2){
        if(!l1 && !l2) return nullptr;
        else if(!l1) return l2;
        else if(!l2) return l1;
        ListNode *nx1=l1,*nx2=l2;
        ListNode *st= minNode(l1,l2);
        ListNode *cur=st;
        while(cur){
            if(cur==nx1) nx1=nx1->next;
            else nx2=nx2->next;
            cur->next= minNode(nx1,nx2);
            cur=cur->next;
        }
        return st;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        int len=int(lists.size());

        while(len>1){
            for(int i=0;i<len/2;++i){
                lists[i]= merge(lists[i],lists[len-1-i]);
            }
            len=(len+1)/2;
        }

        return lists[0];
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
