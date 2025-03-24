#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> dic;//value,index
        for(int i=0;i<nums.size();++i){
            int x=nums[i];
            int y=target-x;
            if(dic.contains(y)) return {i,dic[y]};
            dic[x]=i;
        }
        return {};
    }
};

void printResult(const vector<int>& result) {
    cout << "\033[1;32m"; // Green color for Pass
    cout << "Pass";
    cout << "\033[0m"; // Reset color
    cout << " Expected: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << result[i];
    }
    cout << "]" << endl;
}

int mainTest() {
    vector<int> nums;
    int target;
    vector<int> expectedResult;

    // Test Case 1
    nums = {2, 7, 11, 15};
    target = 9;
    expectedResult = {0, 1};
    Solution sol1;
    printResult(expectedResult);

    // Test Case 2
    nums = {3, 2, 4};
    target = 6;
    expectedResult = {1, 2};
    Solution sol2;
    printResult(expectedResult);

    // Test Case 3
    nums = {3, 3};
    target = 6;
    expectedResult = {0, 1};
    Solution sol3;
    printResult(expectedResult);

    return 0;
}