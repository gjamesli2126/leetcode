#include<bits/stdc++.h>
using namespace std;
constexpr array<pair<int,int>,4> dirs{{
    {0,1},{1,0},{-1,0},{0,-1}
}};
class Solution {
private:
    vector<vector<char>> visited;
    int r_max,c_max;
    void bfs(const vector<vector<int>>& heights,const pair<int,int>& rc,const char& side){
        deque<pair<int,int>> q{rc};
        if(visited[rc.first][rc.second]=='u') visited[rc.first][rc.second]=side;
        else if(visited[rc.first][rc.second]!=side) visited[rc.first][rc.second]='b';
        
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop_front();
            for(const auto& [dr,dc]:dirs){
                int r=r0+dr,c=c0+dc;
                if(r<0 || r>=r_max || c<0 || c>=c_max || visited[r][c]==side || visited[r][c]=='b' || heights[r][c]<heights[r0][c0]) continue;
                q.emplace_back(r,c);//change to emplace_back? ok
                if(visited[r][c]=='u') visited[r][c]=side;
                else if(visited[r][c]!=side) visited[r][c]='b';
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        r_max=heights.size();
        c_max=heights[0].size();
        if(r_max==1 && c_max==1) return {{0,0}};
        visited.resize(r_max,vector<char>(c_max,'u'));//unvisited
        vector<vector<int>> ans;
        //even before running thru whole code give 2 corners 'b'
        
        for(int r=0;r<r_max;r++){//p means pacific, a means atlantic
            bfs(heights,{r,0},'p');//most left side
            bfs(heights,{r,c_max-1},'a');//most right side
        }
        for(int c=0;c<c_max;c++){
            bfs(heights,{0,c},'p');//most top side
            bfs(heights,{r_max-1,c},'a');//most bottom side
        }
        for(int r=0;r<r_max;r++){
            for(int c=0;c<c_max;c++){
                if(visited[r][c]=='b') ans.push_back(vector<int>{r,c});//b means both
            }
        }
        return ans;
    }
};