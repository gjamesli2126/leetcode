#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0,m,r=nums.size()-1;
        while(l<=r){
            m=(l+r)/2;
            if(nums[m]==target) return m;
            //m on the left half
            if(nums[l]<=nums[m]){
                //if target on the left side
                if(nums[l]<=target && target<=nums[m]) r=m-1;
                //if target on the right side
                else if(nums[m]<=target || target<=nums[r]) l=m+1;
                //none of them
                else return -1;
            }
            //m on the right half
            else if(nums[m]<=nums[r]){
                //if target is truly on the right hand side
                if(nums[m]<=target && target<=nums[r]) l=m+1;
                //if target is actually on the left
                else if(nums[l]<=target || target<=nums[m]) r=m-1;
                //none
                else return -1;
            }
        }
        return -1;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        }
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> nums;
        int target;
        int expected;
    };

    vector<TestCase> testCases = {
            {{4,5,6,7,0,1,2}, 0, 4},      // Test case 1
            {{4,5,6,7,0,1,2}, 3, -1},     // Test case 2
            {{1}, 0, -1},                  // Test case 3
            {{1,3,5},3,1},
            {{4,5,6,7,8,1,2,3},8,4},

    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.search(testCases[i].nums, testCases[i].target);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
