#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int search(vector<int>& nums, int target) {
        //bin-sreach with left/right portion determine
        int l=0;
        int r=nums.size();
        while(l<r){
            int mid=l+(r-l)/2;
            if(target==nums[mid]) return mid;
            if(nums[l]<=nums[mid]){//[r,m) m on left portion
                if(nums[l]<=target && target<nums[mid]) r=mid;//target in left
                else l=mid+1;//target on  the right side
            }else{//m on right portion
                if(nums[mid]<target && target<=nums[r-1]) l=mid+1;//on the right portion, r-1 b/c r means not invluded
                else r=mid;
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
