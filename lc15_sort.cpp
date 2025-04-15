#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        //method1 sort && 2 ptr
        sort(nums.begin(),nums.end());//sort to avoid dup value
        for(int p1=0;p1<nums.size();p1++){
            if(p1>0 && nums[p1]==nums[p1-1]) continue;
            int l=p1+1;
            int r=nums.size()-1;
            while(l<r){
                if(nums[p1]+nums[l]+nums[r]<0) l++;
                else if(nums[p1]+nums[l]+nums[r]>0) r--;
                else{
                    ans.push_back({nums[p1],nums[l++],nums[r--]});
                    while(l<r && nums[l]==nums[l-1])l++;
                    while(l<r && nums[r]==nums[r+1])r--;
                }
            }
        }
        return ans;
    }
};

// Helper function to print a vector of ints.
void printVector(const vector<int>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++){
        cout << vec[i] << (i < vec.size() - 1 ? ", " : "");
    }
    cout << "]";
}

// Helper function to print a matrix (vector of vector of ints).
void printMatrix(const vector<vector<int>>& mat) {
    cout << "[";
    for (size_t i = 0; i < mat.size(); i++){
        printVector(mat[i]);
        if(i < mat.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

// Helper function to sort the triplets within a vector of vector<int>.
// We sort each triplet individually and then sort the entire vector lexicographically.
void normalizeTriplets(vector<vector<int>>& triplets) {
    for (auto &triplet : triplets) {
        sort(triplet.begin(), triplet.end());
    }
    sort(triplets.begin(), triplets.end());
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<int> nums, vector<vector<int>> expected) {
    Solution sol;
    vector<vector<int>> result = sol.threeSum(nums);

    // Normalize both result and expected for comparison since order does not matter
    normalizeTriplets(result);
    normalizeTriplets(expected);

    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: threeSum(nums) = ";
        printMatrix(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: threeSum(nums) = ";
        printMatrix(result);
        cout << ", expected ";
        printMatrix(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: nums = [-1,0,1,2,-1,-4]
    // Expected Output: [[-1,-1,2],[-1,0,1]]
    vector<int> input1 = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> expected1 = {{-1, -1, 2}, {-1, 0, 1}};
    runTest(1, input1, expected1);

    // Test Case 2:
    // Input: nums = [0,1,1]
    // Expected Output: []
    vector<int> input2 = {0, 1, 1};
    vector<vector<int>> expected2 = {};
    runTest(2, input2, expected2);

    // Test Case 3:
    // Input: nums = [0,0,0]
    // Expected Output: [[0,0,0]]
    vector<int> input3 = {0, 0, 0};
    vector<vector<int>> expected3 = {{0, 0, 0}};
    runTest(3, input3, expected3);

    return 0;
}