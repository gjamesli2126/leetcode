#include<bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
private:
    int rmax,cmax;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //flattenize the index
        //row=1/cmax
        //col=i%cmax
        //i=0~(rmax*cmax-1)
        rmax=matrix.size();
        cmax=matrix[0].size();
        int l=0;
        int r=rmax*cmax-1;
        while(l<r){
            int mid=l+(r-l)/2;
            //finding the exact match
            int row=mid/cmax;
            int col=mid%cmax;
            if(matrix[row][col]==target) return true;
            if(matrix[row][col]<target) l=mid+1;
            else r=mid;
        }
        return target==matrix[l/cmax][l%cmax];//if equal
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
