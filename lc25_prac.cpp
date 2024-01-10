#include<bits/stdc++.h>
using namespace std;
#define mainTest main
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int val):val(val){}
    ListNode(int val,ListNode *next):val(val),next(next){}
};
class Solution{
private:
    ListNode* reverse(ListNode *dummyHead,ListNode *tail){
        ListNode *newSt=dummyHead->next;
        ListNode *prev=tail->next;
        ListNode *cur=dummyHead->next;
        ListNode *orgNext;
        while(cur!=tail){
            orgNext=cur->next;
            cur->next=prev;
            prev=cur;
            cur=orgNext;
        }
        //at this moment, cur is at the tail BUT we want to let this tail point to it's prev
        cur->next=prev;
        dummyHead->next=cur;

        return newSt;
    }
public:

    ListNode* reverseKGroup(ListNode *head,const int& k){
        ListNode *dummyHead=new ListNode(-1,head);
        ListNode *st=dummyHead;
        ListNode *end=dummyHead;
        int i=0;
        while(end){
            if(i<k){
                end=end->next;
                ++i;
                continue;
            }
            i=0;
            st=reverse(st,end);
            end=st;
        }

        ListNode *newHead=dummyHead->next;
        delete dummyHead;
        return newHead;
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

    vector<pair<vector<int>, int>> testCases = {
            {{1, 2, 3, 4, 5}, 2},  // Test case 1
            {{1, 2, 3, 4, 5}, 3}   // Test case 2
            // Add more test cases here
    };
    vector<vector<int>> exps{
            {2,1,4,3,5},{3,2,1,4,5}
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        ListNode* list = buildList(testCases[i].first);
        ListNode* modifiedList = solution.reverseKGroup(list, testCases[i].second);
        vector<int> result = listToVector(modifiedList);
        // Define the expected output for your test cases
        vector<int> expected=exps[i];
        test(result, expected, i + 1);
    }

    return 0;
}
