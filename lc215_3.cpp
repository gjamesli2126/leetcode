#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
    //using meanHeap with size=k
private:
    priority_queue<int,vector<int>,greater<int>> minHeap;//default is maxHeap in c++
public:
    int findKthLargest(vector<int>& nums, int k) {
        for(int n:nums){
            if(minHeap.size()==k){
                if(minHeap.top()>n) continue;//to avoid ALWAYS push & pop
                minHeap.pop();
            }
            minHeap.push(n);

        }
        return minHeap.top();
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, int k, int expected) {
    Solution sol;
    int result = sol.findKthLargest(nums, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected "
             << expected << " but got " << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [3,2,1,5,6,4], k = 2
    // Expected Output: 5
    runTest(1, {3, 2, 1, 5, 6, 4}, 2, 5);

    // Test Case 2:
    // Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    // Expected Output: 4
    runTest(2, {3, 2, 3, 1, 2, 4, 5, 5, 6}, 4, 4);

    return 0;
}