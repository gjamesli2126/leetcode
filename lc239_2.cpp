#include<bits/stdc++.h>
using namespace std;
#define mainTest main
//Monotonic decreasing deque 可以讓most left變成max
class Solution {
private:
    deque<int> dq;//mono decrease, the left most element=ans
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans(nums.size()-k+1);
        for(int i=0;i<nums.size();++i){
            if(i>=k && dq.front()==nums[i-k]) dq.pop_front();
            while(!dq.empty() && dq.back()<nums[i]) dq.pop_back();
            dq.emplace_back(nums[i]);
            if(i<k-1) continue;
            ans[i-(k-1)]=dq.front();
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
