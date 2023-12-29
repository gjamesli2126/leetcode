#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int shortestSubarray(vector<int>& nums0, int k) {
        vector<long long> nums(nums0.begin(),nums0.end());
        int len=int(nums.size()),minWin=len+1;
        int bp;//fp=d.front()
        deque<unsigned long long> d;
        //using prefixsum
        for(bp=0;bp<len;++bp){
            if(nums[bp]>=k) return 1;
            if(bp>0) nums[bp]+=nums[bp-1];
            if(nums[bp]>=k) minWin=min(minWin,bp+1);
            // if >=k then calc min minWin
            while(!d.empty() && nums[bp]-nums[d.front()]>=k){
                minWin=min(minWin,bp-int(d.front()));
                d.pop_front();
            }
            //if this nums[i] is so small -> to make the queue increment -> popback, meaning reset
            while (!d.empty() && nums[bp]<=nums[d.back()]) d.pop_back();
            d.push_back(bp);
        }

        if(minWin==len+1) return -1;
        return minWin;
    }
};

int mainTest() {
    Solution solution;

    // Test Cases
    vector<pair<vector<int>, int>> testCases = {
            {{1}, 1},                // Example 1
            {{1,2}, 4},              // Example 2
            {{2,-1,2}, 3}      ,      // Example 3
            {{48,99,37,4,-31},140},
            {{ 84,-37,32,40,95},167},
    };

    // Expected Outputs
    vector<int> expectedOutputs = {1, -1, 3,2,3}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.shortestSubarray(testCases[i].first, testCases[i].second);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
