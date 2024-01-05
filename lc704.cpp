#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len=int(nums.size());
        int mid;
        int lb=0,ub=len-1;
        while(lb<=ub){
            mid=(ub+lb)/2;
            if(nums[mid]==target) return mid;
            else if(nums[mid]>target){
                ub=mid-1;
            }
            else if(nums[mid]<target){
                lb=mid+1;
            }
        }
        return -1;
    }
    int search_stl(vector<int>& nums, int target) {
        auto it=find(nums.begin(),nums.end(),target);
        if(it==nums.end()) return -1;
        return it-nums.begin();
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
            {{-1, 0, 3, 5, 9, 12}, 9, 4},  // Test case 1
            {{-1, 0, 3, 5, 9, 12}, 2, -1}, // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.search(testCases[i].nums, testCases[i].target);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
