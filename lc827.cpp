#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    const int flatDir[5]={1,0,-1,0,1};
    inline bool validRC(const vector<vector<int>>& grid,int r,int c){
        return r<grid.size() && r>=0 && c<grid[0].size() && c>=0;
    }
    //perform dfs to find area
    unsigned int dfsCalcAreaOfIsland(vector<vector<int>>& grid,int isLandID,int r,int c){
        unsigned int area=1;//assume got val 1 in grid
        grid[r][c]=isLandID;
        for(int i=0;i<4;i++){
            int new_r=r+flatDir[i];
            int new_c=c+flatDir[i+1];
            if(!validRC(grid,new_r,new_c) || grid[new_r][new_c]!=1) continue;
            area+= dfsCalcAreaOfIsland(grid,isLandID,new_r,new_c);
        }
        return area;
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        //step 1: build up islandArea_vec, [_,_,35,75,11,...];, islandID from 2 to n^2
        vector<unsigned int> islandArea={0,0};
        unsigned int maxIslandArea=0;
        int landID=2;
        for(int r=0;r<grid.size();r++){
            for(int c=0;c<grid[0].size();c++){
                if(validRC(grid,r,c) && grid[r][c]==1){//if unvisited && is land
                    unsigned int area= dfsCalcAreaOfIsland(grid,landID,r,c);
                    islandArea.emplace_back(area);
                    maxIslandArea= max(maxIslandArea,area);
                    grid[r][c]=landID;
                    ++landID;
                }
            }
        }
        //if all water
        if(islandArea.size()==2) return 1;

        //step2: try water area with flipped

        for(int r=0;r<grid.size();r++){
            for(int c=0;c<grid[0].size();c++){
                unordered_set<int> landIDVisisted;
                unsigned int combinedArea=1;//if this (r,c) is flipped
                if(grid[r][c]==0){
                    //find all neighbors that has land
                    for(int i=0;i<4;i++){
                        int new_r=r+flatDir[i];
                        int new_c=c+flatDir[i+1];
                        if(!validRC(grid,new_r,new_c)) continue;
                        int landID=grid[new_r][new_c];
                        if(landIDVisisted.contains(landID)) continue;
                        landIDVisisted.insert(landID);
                        combinedArea+=islandArea[landID];
                    }
                }
                maxIslandArea=max(maxIslandArea,combinedArea);
            }
        }
        //handle if no water at all
//        if(!maxIslandArea) return grid.size()*grid[0].size();
        return maxIslandArea;
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