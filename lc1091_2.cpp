#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
private:
    int rmax,cmax;
    vector<pair<int,int>> dirs{
            {1,0},{-1,0},{0,1},{0,-1},
            {1,1},{-1,-1},{1,-1},{-1,1}
    };
    inline bool validcoord(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        //cannot use ans_counter following along the traverse, because we may traverse a dead route, and cannot count it as a step
        if(grid.empty()) return -1;
        rmax=grid.size();
        cmax=grid[0].size();
        if(grid[0][0]==1 || grid[rmax-1][cmax-1]==1) return -1;
        queue<pair<int,int>> q;
        grid[0][0]=1;
        q.emplace(0,0);
        while(!q.empty()){
            auto [r,c]=q.front();
            q.pop();
            if(r==rmax-1 && c==cmax-1) return grid[rmax-1][cmax-1];
            for(auto [dr,dc]:dirs){
                if(!validcoord(r+dr,c+dc) || grid[r+dr][c+dc]!=0) continue;
                grid[r+dr][c+dc]=grid[r][c]+1;//put here not at the front so that won't double added;
                q.emplace(r+dr,c+dc);
            }
        }
        return -1;
    }
};
void runTest(int testNum, vector<vector<int>> grid, int expected) {
//    if(testNum!=2) return;
    Solution sol;
    int result = sol.shortestPathBinaryMatrix(grid);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: shortestPathBinaryMatrix(grid) = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: shortestPathBinaryMatrix(grid) = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: grid = [[0,1],[1,0]]
    // Expected Output: 2
    runTest(1, {{0,1},{1,0}}, 2);

    // Test Case 2:
    // Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
    // Expected Output: 4
    runTest(2, {{0,0,0},{1,1,0},{1,1,0}}, 4);

    // Test Case 3:
    // Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
    // Expected Output: -1
    runTest(3, {{1,0,0},{1,1,0},{1,1,0}}, -1);
    runTest(4,{{0,0,0},{1,1,0},{1,1,1}},-1);

    return 0;
}