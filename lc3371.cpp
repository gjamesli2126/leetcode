#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        //space O(n), time O(n)
        int sum= accumulate(nums.begin(),nums.end(),0);
        int max_outlier=INT_MIN;
        int sumx2,sumx1;
        unordered_map<int,int> nmap;//num:count
        for(int n:nums) nmap[n]++;
        for(int n:nums){
            sumx2=sum-n;
            if(sumx2%2!=0) continue;
            sumx1=sumx2/2;//sumx1 might not exist in the nums, so need to find if contain
            if(nmap.contains(sumx1) && (sumx1!=n || nmap[sumx1]>1)) max_outlier= max(max_outlier,n);
        }

        return max_outlier;
    }
};

void runTest(int testNum, vector<int> nums, int expected) {
    Solution sol;
    int result = sol.getLargestOutlier(nums);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: getLargestOutlier(nums) = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: getLargestOutlier(nums) = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums = [2,3,5,10]
    // Explanation: The special numbers could be 2 and 3, their sum is 5, and the outlier is 10.
    // Expected Output: 10
    runTest(1, {2, 3, 5, 10}, 10);

    // Example 2:
    // Input: nums = [-2,-1,-3,-6,4]
    // Explanation: The special numbers could be -2, -1, and -3, their sum is -6, and the outlier is 4.
    // Expected Output: 4
    runTest(2, {-2, -1, -3, -6, 4}, 4);

    // Example 3:
    // Input: nums = [1,1,1,1,1,5,5]
    // Explanation: The special numbers could be five 1's (sum = 5) and the outlier is the other 5.
    // Expected Output: 5
    runTest(3, {1, 1, 1, 1, 1, 5, 5}, 5);
    runTest(4,{166,-854,166},-854);
    runTest(5,{6,-31,50,-35,41,37,-42,13},-35);

    return 0;
}