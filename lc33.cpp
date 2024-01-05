#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0,r=nums.size()-1,m;
        while (l <= r) {
            int m =  (r + l) / 2;
            if (nums[m] == target) {
                return m; // Target found.
            }

            // mid at Left sorted half
            if (nums[l] <= nums[m]) {
                if (target >= nums[l] && target < nums[m]) {
                    r = m - 1; // Target in the left half.
                } else if (target > nums[m] || target <= nums[r]) {// NOt:target<=nums[r] for outliers
                    l = m + 1; // Target not in the left half.
                }else if(target>nums[r]) return -1;// the target is on the right side of upper bound

            }

            // mid at Right sorted half
            else if (nums[m] <= nums[r]) {
                if (target > nums[m] && target <= nums[r]) {
                    l = m + 1; // Target in the right half.
                } else if (target < nums[m] || target >= nums[l]) {//NOT target>=nums[l] for outliers
                    r = m - 1; // Target not in the right half.
                }else if(target<nums[l]) return -1;// the target is on the left side of lower bound
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
