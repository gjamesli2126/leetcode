#include<bits/stdc++.h>
using namespace std;
constexpr array<pair<int,int>,4> dirs{{
    {0,1},{1,0},{-1,0},{0,-1}
}};
class Solution {
private:
    int r_max,c_max;
    set<pair<int,int>> protect;
    void bfs(vector<vector<char>>& board,const pair<int,int>& rc){
        if(board[rc.first][rc.second]=='X' || protect.find(rc)!=protect.end()) return;
        deque<pair<int,int>> q{rc};
        protect.insert(rc);
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop_front();
            for(const auto& [dr,dc]:dirs){
                int r=r0+dr,c=c0+dc;
                if(r<0 || r>=r_max || c<0 || c>=c_max || board[r][c]=='X' || protect.find({r,c})!=protect.end()) continue;
                q.emplace_back(r,c);
                protect.insert({r,c});
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        r_max=board.size();
        c_max=board[0].size();
        for(int r=0;r<r_max;r++){
            bfs(board,{r,0});//left side
            bfs(board,{r,c_max-1});//right side
        }
        for(int c=0;c<c_max;c++){
            bfs(board,{0,c});
            bfs(board,{r_max-1,c});
        }
        //non-protected element should be 'X'
        for(int r=0;r<r_max;r++){
            for(int c=0;c<c_max;c++){
                if(protect.find({r,c})==protect.end()) board[r][c]='X';
            }
        }
    }
};