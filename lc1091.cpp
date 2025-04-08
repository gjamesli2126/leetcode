#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int rmax,cmax;
    vector<vector<int>> *grid_ptr;
    const pair<int,int> dirs[8]={{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
    bool chkValid(int r,int c){
        return r>=0 && r<=rmax && c>=0 && c<=cmax && (*grid_ptr)[r][c]!=1;
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        //using bfs, val=0(unvisited),1(wall), 2~inf(step1~inf)
        rmax= grid.size()-1;
        cmax=grid[0].size()-1;
        if(grid[0][0]==1 || grid[rmax][cmax]==1) return -1;
        grid_ptr=&grid;
        queue<pair<int,int>> q;
        q.emplace(0,0);
        bool q_the_last=false;
        while(!q.empty()){
            auto [r,c]=q.front();
            if(r==rmax && c==cmax) q_the_last=true;
            q.pop();
            //for 8 dir
            for(int i=0;i<8;i++){
                int newR=r+dirs[i].first;
                int newC=c+dirs[i].second;
                if(!chkValid(newR,newC)) continue;
                //compare part
                if(!grid[newR][newC]) {
                    grid[newR][newC] = grid[r][c] + 1;
                    //que in
                    q.emplace(newR,newC);
                }
                else grid[newR][newC]= min(grid[newR][newC],1+grid[r][c]);//just modify
            }
        }
        return q_the_last?grid[rmax][cmax]+1:-1;
    }
};

void runTest(int testNum, vector<vector<int>> grid, int expected) {
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