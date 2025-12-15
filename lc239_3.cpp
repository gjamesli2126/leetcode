#include<bits/stdc++.h>
using namespace std;
#define mainTest main
//Monotonic decreasing deque 可以讓most left變成max 然後要存的是 index才可以知道是否刪
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        int sz=nums.size();
        vector<int> ans(sz-k+1);
        for(int i=0;i<sz;i++){
            //if out of scope
            if(!dq.empty() && dq.front()==i-k) dq.pop_front();
            while(!dq.empty() && nums[dq.back()]<nums[i]) dq.pop_back();
            dq.emplace_back(i);
            //only if the window established can we add to ans
            if(i>=k-1) ans[i-k+1]=nums[dq.front()];
        }
        return ans;
    }
};

int mainTest() {
    auto test = [](const vector<int>& obtained, const vector<int>& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size() - 1 ? ", " : "");
        }
        cout << "], Obtained: [";
        for (int i = 0; i < obtained.size(); i++) {
            cout << obtained[i] << (i < obtained.size() - 1 ? ", " : "");
        }
        cout << "]" << RESET << endl;
    };

    struct TestCase {
        vector<int> nums;
        int k;
        vector<int> expected;
    };

    vector<TestCase> testCases = {
            {{1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}},  // Test case 1
            {{1}, 1, {1}},                             // Test case 2
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        Solution solution;
        vector<int> result = solution.maxSlidingWindow(testCases[i].nums, testCases[i].k);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
