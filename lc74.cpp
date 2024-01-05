#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int cNum;
    pair<int,int> linIndTo2DInd(const int& i){
        return {i/cNum,i%cNum};//which r,c
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int len=int(matrix.size()*matrix[0].size());
        cNum=matrix[0].size();
        int lb=0,ub=len-1,mid;
        while(lb<=ub){
            mid=(lb+ub)/2;
            auto [rMid,cMid] = linIndTo2DInd(mid);
            if(matrix[rMid][cMid]==target) return true;
            if(matrix[rMid][cMid]>target){
                ub=mid-1;
            }
            else lb=mid+1;
        }
        return false;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](bool obtained, bool expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected: " << boolalpha << expected << ", Obtained: " << boolalpha << obtained << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected: " << boolalpha << expected << ", Obtained: " << boolalpha << obtained << RESET << endl;
        }
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<vector<int>> matrix;
        int target;
        bool expected;
    };

    vector<TestCase> testCases = {
            {{{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 3, true},  // Test case 1
            {{{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 13, false}, // Test case 2
            // Add more test cases here
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        bool result = solution.searchMatrix(testCases[i].matrix, testCases[i].target);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
