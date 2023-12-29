#include<bits/stdc++.h>
using namespace std;
constexpr array<pair<int,int>,4> dirs{{{0,1},{1,0},{-1,0},{0,-1}}};
class Solution {
private:
    int r_max,c_max;
    // static const vector<pair<int,int>> dirs;
    int bfs2Area(vector<vector<int>>& grid,pair<int,int> rc){
        deque<pair<int,int>> q{rc};
        grid[rc.first][rc.second]=-1;
        int area=0;
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop_front();
            
            area++;
            for(const auto& [dr,dc]:dirs){
                int r=r0+dr,c=c0+dc;
                if(r<0 || r>=r_max || c<0 || c>=c_max || grid[r][c]!=1) continue;
                q.push_back({r,c});
                grid[r][c]=-1;//change this part to visited imm to avoid add w/ dup
            }
        }
        return area;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea=0;
        r_max=grid.size();
        c_max=grid[0].size();
        for(int r=0;r<r_max;r++){
            for(int c=0;c<c_max;c++){
                if(grid[r][c]==1) maxArea=max(maxArea,bfs2Area(grid,{r,c}));
            }
        }
        return maxArea;
    }
};