#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_map<int,vector<int>> v_is;
public:
    Solution(vector<int>& nums) {
        for(int i=0;i<nums.size();i++) v_is[nums[i]].push_back(i);
    }

    int pick(int target) {

        return v_is[target][rand()%v_is[target].size()];
    }
};

bool isInSet(int val, const vector<int>& valid) {
    for (int x : valid) {
        if (val == x) return true;
    }
    return false;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum) {
    vector<int> nums = {1, 2, 3, 3, 3};
    Solution sol(nums);

    // Call pick(3) - expected result should be one of {2, 3, 4}
    int res1 = sol.pick(3);
    bool pass1 = isInSet(res1, {2, 3, 4});

    // Call pick(1) - expected result should be 0
    int res2 = sol.pick(1);
    bool pass2 = (res2 == 0);

    // Call pick(3) again - expected result should be one of {2, 3, 4}
    int res3 = sol.pick(3);
    bool pass3 = isInSet(res3, {2, 3, 4});

    if (pass1 && pass2 && pass3) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "pick(3) first call: got " << res1 << " (expected one of {2,3,4})" << endl;
        cout << "pick(1): got " << res2 << " (expected 0)" << endl;
        cout << "pick(3) second call: got " << res3 << " (expected one of {2,3,4})" << endl;
    }
}

int testMain(){
    runTest(1);
    return 0;
}