#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int findNextInd(const vector<int>& nums, int tar){
        int l=0,r=nums.size()-1;
        if(tar<=nums[0]) return 0;
        else if(tar>=nums[r]) return r+1;
        int mid=0;
        while (l<r){
            mid=l+(r-l)/2;
            if(nums[mid]<=tar) l=mid+1;
            else r=mid;
        }
        return l;
    }
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> ans;
        if(nums.empty()){
            ans.push_back({lower,upper});
            return ans;
        }
        // 2  bin-search(find lower & upper)
        int lowInd= findNextInd(nums,lower);
        int highInd= findNextInd(nums,upper)-1;


        //O(ipper-lower)
        if(lower<nums[0]) ans.push_back({lower,nums[0]-1});

        for(int i=lowInd;i<highInd;i++){
            int start = nums[i] + 1;
            int end   = nums[i + 1] - 1;
            if(start<=end) ans.push_back({start,end});
        }
        if(nums.back()<upper) ans.push_back({nums.back()+1,upper});
        return ans;
    }
};

// Helper to compare two lists of ranges
bool equalRanges(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Helper to print ranges
void printRanges(const vector<vector<int>>& ranges) {
    cout << "[";
    for (size_t i = 0; i < ranges.size(); ++i) {
        cout << "[" << ranges[i][0] << "," << ranges[i][1] << "]";
        if (i + 1 < ranges.size()) cout << ",";
    }
    cout << "]";
}

// Helper to run a test case
void runTest(int testNum,
             vector<int> nums,
             int lower,
             int upper,
             vector<vector<int>> expected) {
    Solution sol;
    auto result = sol.findMissingRanges(nums, lower, upper);
    if (equalRanges(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: ";
        printRanges(expected);
        cout << "\nGot:      ";
        printRanges(result);
        cout << "\n";
    }
}

int testMain(){
    // Example 1:
    // nums = [0,1,3,50,75], lower = 0, upper = 99
    // Output: [[2,2],[4,49],[51,74],[76,99]]
    runTest(1,
            {0,1,3,50,75},
            0, 99,
            {{2,2},{4,49},{51,74},{76,99}}
    );

    // Example 2:
    // nums = [-1], lower = -1, upper = -1
    // Output: []
    runTest(2,
            {-1},
            -1, -1,
            {}
    );

    return 0;
}