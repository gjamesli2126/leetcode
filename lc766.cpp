#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
//private:
//    bool isValid(int r,int c,vector<vector<int>>& mat){
//        return r>=0 && c>=0 && r<mat.size() && c<mat[0].size();
//    }
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        //直＋橫
        for(int C=0;C<matrix[0].size();C++){
            for(int c=C+1,r=1;c<matrix[0].size() && r<matrix.size();c++,r++){
                if(matrix[r][c]!=matrix[r-1][c-1]) return false;
            }
        }
        for(int R=1;R<matrix.size();R++){
            for(int c=1,r=R+1;c<matrix[0].size() && r<matrix.size();c++,r++){
                if(matrix[r][c]!=matrix[r-1][c-1]) return false;
            }
        }
        return true;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> matrix, bool expected) {
    Solution sol;
    bool result = sol.isToeplitzMatrix(matrix);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isToeplitzMatrix(...) = "
             << (result ? "true" : "false") << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isToeplitzMatrix(...) = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: matrix = [[1,2,3,4],
    //                  [5,1,2,3],
    //                  [9,5,1,2]]
    // Output: true
    runTest(1, {
            {1,2,3,4},
            {5,1,2,3},
            {9,5,1,2}
    }, true);

    // Example 2:
    // Input: matrix = [[1,2],
    //                  [2,2]]
    // Output: false
    runTest(2, {
            {1,2},
            {2,2}
    }, false);

    return 0;
}