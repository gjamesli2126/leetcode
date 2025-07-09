#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
private:
    vector<int> dirs={1,0,-1,0,1};
    int rmax,cmax;
    inline bool isValid(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
    int bfs(vector<vector<int>>& grid,int r0,int c0,const int& landID){
        queue<pair<int,int>> q;
        q.emplace(r0,c0);
        int area=0;
        while(!q.empty()){
            auto [r,c]=q.front();
            q.pop();
            grid[r][c]=landID;
            ++area;
            //look for 4 dirs;
            for(int i=0;i<4;i++){
                int newR=dirs[i]+r;
                int newC=dirs[i+1]+c;
                if(!isValid(newR,newC) || grid[newR][newC]!=1) continue;
                q.emplace(newR,newC);
                grid[newR][newC]=landID;
            }
        }
        return area;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        //using DFS to and store the landID to the matrix
        rmax=grid.size();
        cmax=grid[0].size();
        unordered_map<int,int> ID_area;
        int ID=2;
        bool hasZero=false;
        for(int r=0;r<rmax;r++){
            for(int c=0;c<cmax;c++){
                if(!grid[r][c]) hasZero= true;
                if(grid[r][c]!=1) continue;
                ID_area[ID]= bfs(grid,r,c,ID);
                ID++;
            }
        }
        if(!hasZero) return rmax*cmax;
        //try all zeros to connnect
       int global_max=0;
       for(int r=0;r<rmax;r++){
           for(int c=0;c<cmax;c++){
               if(grid[r][c]!=0) continue;
               //find 4 dirs has exist landID;
               unordered_set<int> visited_islandID;//same landID cannot be double counted;
               int area=0;
               for(int i=0;i<4;i++){
                   int newR=r+dirs[i];
                   int newC=c+dirs[i+1];
                   if(!isValid(newR,newC)) continue;
                   int landID=grid[newR][newC];
                   if(landID<2 || visited_islandID.contains(landID)) continue;
                   visited_islandID.insert(landID);
                   area+=ID_area[landID];
               }
               global_max= max(global_max,area);
           }
       }

       return 1+global_max;
    }
};
void runTest(int testNum, vector<vector<int>> grid, int expected) {
    Solution sol;
    int result = sol.largestIsland(grid);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: largestIsland(grid) = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: largestIsland(grid) = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: grid = [[1,0],[0,1]]
    // Expected Output: 3
    runTest(1, {{1, 0}, {0, 1}}, 3);

    // Test Case 2:
    // Input: grid = [[1,1],[1,0]]
    // Expected Output: 4
    runTest(2, {{1, 1}, {1, 0}}, 4);

    // Test Case 3:
    // Input: grid = [[1,1],[1,1]]
    // Expected Output: 4
    runTest(3, {{1, 1}, {1, 1}}, 4);

    runTest(4,{{1,0,0,1,1},{1,0,0,1,0},{1,1,1,1,1},{1,1,1,0,1},{0,0,0,1,0}},16);
    return 0;
}