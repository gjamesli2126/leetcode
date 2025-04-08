#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int rmax,cmax;
    inline bool boundchk(int r,int c){
        return r>=0 && r<rmax && c>=0 && c<cmax;
    }
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        /*The reason that this is faster:
         * pre-calc r_low & r_high bound instead of checking at every loop (time complex is the same tho)
         *
         * */
        rmax=mat.size();
        cmax=mat[0].size();
        if(!rmax || !cmax) return {};
        vector<int> ans;
        ans.reserve(rmax*cmax);
        for(int attempt=0;attempt<rmax+cmax-1;++attempt){
            int rlow_ind=max(0,attempt-(cmax-1));
            int rhigh_ind=min(attempt,rmax-1);
            //dir1 up rhigh->rlow
            if(attempt%2==0) for(int i=rhigh_ind;i>=rlow_ind;i--) ans.push_back(mat[i][attempt-i]);
            //dir2 down rlow -> rhigh
            else for(int i=rlow_ind;i<=rhigh_ind;i++) ans.push_back(mat[i][attempt-i]);
        }
        return ans;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> mat, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.findDiagonalOrder(mat);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: findDiagonalOrder(mat) = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: findDiagonalOrder(mat) = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "], expected [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "]\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
    // Expected Output: [1,2,4,7,5,3,6,8,9]
    runTest(1, {{1,2,3}, {4,5,6}, {7,8,9}}, {1,2,4,7,5,3,6,8,9});

    // Test Case 2:
    // Input: mat = [[1,2],[3,4]]
    // Expected Output: [1,2,3,4]
    runTest(2, {{1,2}, {3,4}}, {1,2,3,4});

    runTest(3,{
            {1,2,3,4,5},
            {6,7,8,9,10},
            {11,12,13,14,15},
            {16,17,18,19,20}
    },{1,2,6,11,7,3,4,8,12,16,17,13,9,5,10,14,18,19,15,20});
    return 0;
}