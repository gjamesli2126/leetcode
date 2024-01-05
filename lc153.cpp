#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int findMin(const vector<int>& nums){
        int r=nums.size()-1;
        int l=0,m;
        while(l<=r){
            m=(l+r)/2;
            if(nums[r]<=nums[m]) l=m+1;
            else r=m;
        }
        return nums[m];
    }
    int findMin_org(vector<int>& nums) {
        int r=nums.size()-1;
        int l=0,m,ans=INT_MAX;
        while (l<r){
            m=(l+r)/2;
            if(nums[m]<nums[l] && nums[m]<nums[r]) r--,l++;
            else if(nums[l]<nums[r]) r=m-1;
            else if(nums[l]>nums[r]) l=m+1;
            ans= min(nums[m],ans);
        }
        return min(nums[l],ans);
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN<< "[Pass] " ;
        } else {
            cout << RED << "[Fail] " ;// testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        }
        cout<<RESET<<testName << "\t-Exp: " << expected << ", Act: " << obtained << RESET << endl;
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> nums;
        int expected;
    };

    vector<TestCase> testCases = {
            {{3,4,5,1,2}, 1},      // Test case 1
            {{4,5,6,7,0,1,2}, 0},  // Test case 2
            {{11,13,15,17}, 11},    // Test case 3
            {{3,1,2},1},
            {{5,1,2,3,4},1},
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.findMin(testCases[i].nums);
        test(result, testCases[i].expected, "test case " + to_string(i + 1));
    }

    return 0;
}
