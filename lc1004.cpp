#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int eqOnesCount = 0;
        int res = 0;
        int fp, bp;
        int len = int(nums.size());
        for (fp = 0, bp = 0; bp < len; bp++) {
            if (nums[bp] == 1 || k>=0) {
                ++eqOnesCount;
                k -= nums[bp] == 0;
            }
            while (k < 0) { //need to give back zeros
                --eqOnesCount;
                if (nums[fp] == 0) ++k;
                ++fp;
            }
            res = max(res, bp - fp + 1);
        }
        return res;
    }
};

int mainTest() {
    Solution solution;

    // Test Cases
    vector<pair<vector<int>, int>> testCases = {
            {{1,1,1,0,0,0,1,1,1,1,0}, 2},  // Example 1
            {{0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3}  // Example 2
    };

    // Expected Outputs
    vector<int> expectedOutputs = {6, 10};

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.longestOnes(testCases[i].first, testCases[i].second);
        bool status = (actual == expectedOutputs[i]);

        cout << "Test " << i + 1 << ": "
             << "Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}

