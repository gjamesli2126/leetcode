#include <bits/stdc++.h>
#define testMain main
using namespace std;
class SparseVector {
public:
    vector<pair<int,int>> ivs;
    SparseVector(vector<int> &nums) {
        for(int i=0;i<nums.size();i++) if(nums[i]) ivs.emplace_back(i,nums[i]);
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        vector<pair<int,int>> othivs=vec.ivs;
        int i=0,j=0;
        int ans=0;
        while(i<ivs.size() && j<othivs.size()){
            auto [ii,iv]=ivs[i];
            auto [jj,jv]=othivs[j];
            if(ii==jj) {
                ans += iv * jv;
                i++,j++;
            }
            else if(ii<jj) i++;
            else j++;
        }
        return ans;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums1, vector<int> nums2, int expected) {
    SparseVector v1(nums1);
    SparseVector v2(nums2);
    int result = v1.dotProduct(v2);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: result = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: expected " << expected << " but got "
             << result << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
    // Expected Output: 8
    runTest(1, {1,0,0,2,3}, {0,3,0,4,0}, 8);

    // Example 2:
    // Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
    // Expected Output: 0
    runTest(2, {0,1,0,0,0}, {0,0,0,0,2}, 0);

    // Example 3:
    // Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
    // Expected Output: 6
    runTest(3, {0,1,0,0,2,0,0}, {1,0,0,0,3,0,4}, 6);

    return 0;
}