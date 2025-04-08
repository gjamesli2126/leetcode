#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int rmax,cmax;
    inline bool boundchk(int r,int c){
        return r>=0 && r<=rmax && c>=0 && c<=cmax;
    }
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int r=0,c=0;

        rmax=mat.size()-1;
        cmax=mat[0].size()-1;
        vector<int> ans;
        ans.reserve((rmax+1)*(cmax+1));
        int attempt=0;
        int dir=1;// 1--->, -1 <----

        while(attempt<=rmax+cmax+1){
            if(dir==1){
                r=attempt;
                c=0;
                while(r>=0) {
                    if(boundchk(r,c)) ans.push_back(mat[r][c]);
                    r--;
                    c++;
                }
            }
            else{//-1
                r=0;
                c=attempt;
                while(c>=0){
                    if(boundchk(r,c)) ans.push_back(mat[r][c]);
                        r++;
                        c--;
                }
            }
            dir*=-1;
            ++attempt;
        }
//        ans.push_back(mat[rmax][cmax]);
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