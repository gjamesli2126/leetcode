#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
private:
    vector<int> dirs16={1,0,
                        1,1,
                        0,1,
                        -1,1,
                        -1,0,
                        -1,-1,
                        0,-1,
                        1,-1
    };
    int rmax,cmax;
    inline bool isvalid(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        //using BFS
        rmax= grid.size(),cmax=grid[0].size();
        if(grid[0][0]==1 || grid[rmax-1][cmax-1]==1) return -1;//immpsobile to traverse from start to end
        //offset of steps is 2
        queue<pair<int,int>> q;
        q.emplace(0,0);
        grid[0][0]=2;
        while(!q.empty()){
            auto [r,c]=q.front();
            q.pop();
            for(int i=0;i<15;i++){
                int newR=r+dirs16[i];
                int newC=c+dirs16[i+1];
                if(isvalid(newR,newC) && grid[newR][newC]==0){
                    q.emplace(newR,newC);
//                    if(grid[r][c]+1<grid[newR][newC]) grid[newR][newC]=1+grid[newR][newC];//need to use min!!!--no need
                    grid[newR][newC]=grid[r][c]+1;
                }
            }
        }
        return grid[rmax-1][cmax-1]==0?-1:grid[rmax-1][cmax-1]-1;
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