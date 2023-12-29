#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int minSubArrayLen(int k, vector<int>& nums) {
        int len=int(nums.size()),minWin=len+1;
        int fp,bp,localSum=0;
        for(fp=0,bp=0;bp<len;++bp){
            if(nums[bp]>=k) return 1;
            localSum+=nums[bp];
            while(localSum>=k){
                minWin=min(minWin,bp-fp+1);
                localSum-=nums[fp];
                ++fp;
            }
        }
        if(minWin==len+1) return 0;
        return minWin;
    }
};
int mainTest() {
    Solution solution;

    // Test Cases
    vector<pair<int, vector<int>>> testCases = {
            {7, {2, 3, 1, 2, 4, 3}},  // Example 1
            {4, {1, 4, 4}},           // Example 2
            {11, {1, 1, 1, 1, 1, 1, 1, 1}} // Example 3
    };

    // Expected Outputs
    vector<int> expectedOutputs = {2, 1, 0}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.minSubArrayLen(testCases[i].first, testCases[i].second);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Target: " << testCases[i].first << ", "
             << "Nums: [";
        for (size_t j = 0; j < testCases[i].second.size(); ++j) {
            cout << testCases[i].second[j];
            if (j < testCases[i].second.size() - 1) cout << ", ";
        }
        cout << "], Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}