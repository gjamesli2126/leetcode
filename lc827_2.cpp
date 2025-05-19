#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
private:
    vector<int> landID_area;//index is landID(from 1)
    int rmax,cmax;
    bool validRC(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
    vector<int> dirs={1,0,-1,0,1};
    int calcIslandArea(vector<vector<int>>& grid,int r,int c,int islandID){
        int area=1;//assuming this cell has stored 1
        grid[r][c]=islandID;
        for(int i=0;i<4;i++){
            int newr=r+dirs[i];
            int newc=c+dirs[i+1];
            if(!validRC(newr,newc) || grid[newr][newc]!=1) continue;
            area+= calcIslandArea(grid,newr,newc,islandID);
        }
        return area;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        //using dfs find the land area first then Store the land ID onto each cell, if it was 1. After that,
        //see the surround landID, and add 1 onto the sum. and update the global max area.
        rmax=grid.size();
        cmax=grid[0].size();
        landID_area={0,0};//id start from 2
        int global_area_max=0;
        int landID=1;//id start from 2
        for(int r=0;r<rmax;r++){
            for(int c=0;c<cmax;c++){
                if(grid[r][c]!=1) continue;
                landID_area.push_back(calcIslandArea(grid,r,c,++landID));
//                global_area_max=max(global_area_max,landID_area.back());
            }
        }
        if(landID_area.empty()) return 1;
        //built each island's area. Now let's try flipping each 0 to 1
        //if 2 island are on the same islandID, do not add a gain
        for(int r=0;r<rmax;r++){
            for(int c=0;c<cmax;c++){
                if(grid[r][c]!=0) continue;
                int local_area=1;//self
                unordered_set<int> visited_landID;
                for(int i=0;i<4;i++){
                    int newr=r+dirs[i];
                    int newc=c+dirs[i+1];
                    if(!validRC(newr,newc) || grid[newr][newc]==0 || visited_landID.contains(grid[newr][newc])) continue;
                    visited_landID.insert(grid[newr][newc]);
                    local_area+=landID_area[grid[newr][newc]];
                }
                global_area_max= max(global_area_max,local_area);
            }
        }
        return global_area_max?global_area_max:rmax*cmax;
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

    return 0;
}