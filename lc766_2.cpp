#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int rmax,cmax;
    bool validRC(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
    bool validDiag(int r0,int c0,vector<vector<int>>& mat){
        int target=mat[r0][c0];
        for(int r=r0+1,c=c0+1;r<rmax && c<cmax;r++,c++){
            if(!validRC(r,c)) return true;
            if(target!=mat[r][c]) return false;
        }
        return true;
    }
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        rmax=matrix.size();
        cmax=matrix[0].size();
        for(int r=0;r<rmax;r++){
            //do diag
            if(!validDiag(r,0,matrix)) return false;
        }
        for(int c=0;c<cmax;c++){
            if(!validDiag(0,c,matrix)) return false;
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