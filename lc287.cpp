#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if(nums.size()==2) return nums[0];
        int slow=nums[0];// 都先提前走一步，避免while loop condition 很大坨
        int fast=nums[nums[0]];
        while(slow!=fast){
            slow=nums[slow];
            fast=nums[fast];
            fast=nums[fast];
        }
        slow=0;
        while(slow!=fast){
            slow=nums[slow];
            fast=nums[fast];
        }
        assert(slow==fast);
        return slow;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, int testNum) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        cout << (obtained == expected ? GREEN + "PASS: Test Case " + to_string(testNum) : RED + "FAIL: Test Case " + to_string(testNum));
        if (obtained != expected) {
            cout << " - Expected: " << RED << expected << RESET << ", Obtained: " << RED << obtained << RESET;
        }
        cout << endl;
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> nums;
        int expected;
    };

    vector<TestCase> testCases = {
            {{1, 3, 4, 2, 2}, 2},  // Test case 1
            {{3, 1, 3, 4, 2}, 3},  // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.findDuplicate(testCases[i].nums);
        test(result, testCases[i].expected, i + 1);
    }

    return 0;
}
