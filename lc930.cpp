#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int atMostK(const vector<int>& nums,int goal){
        if(goal<0) return 0;
        int fp,bp,res=0,len=int(nums.size());
        for(fp=0,bp=0;bp<len;++bp){
            goal-=nums[bp];
            while(fp<len&&goal<0){
                goal+=nums[fp];
                ++fp;
                cout<<fp<<endl;
            }
            res+=bp-fp+1;
        }
        return res;
    }
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMostK(nums,goal)- atMostK(nums,goal-1);
    }
};

int mainTest() {
    Solution solution;

    // Test Cases
    vector<pair<vector<int>, int>> testCases = {
            {{1,0,1,0,1}, 2},  // Example 1
            {{0,0,0,0,0}, 0},  // Example 2
            // Add more test cases as needed
    };

    // Expected Outputs
    vector<int> expectedOutputs = {4, 15}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.numSubarraysWithSum(testCases[i].first, testCases[i].second);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
