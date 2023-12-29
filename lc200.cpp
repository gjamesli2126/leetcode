#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const vector<pair<int,int> > dir;
    int r_max,c_max;
    void dfs(vector<vector<char> >& grid,const pair<int,int>& rc){
        stack<pair<int,int> > stk;
        stk.push(rc);
        while(!stk.empty()){
            auto [r0,c0]=stk.top();
            stk.pop();
            grid[r0][c0]='2';
            for(const auto &[dr,dc]:dir){
                int r=r0+dr,c=c0+dc;
                if(r<0 || r>=r_max || c<0 || c>=c_max || grid[r][c]!='1') continue;
                stk.push({r,c});
            }
        }
    }
    int numIslands(vector<vector<char> >& grid) {
        //put -1 inside visited
        int islandNum=0;
        r_max=grid.size();
        c_max=grid[0].size();
        for(int r=0;r<r_max;r++){
            for(int c=0;c<c_max;c++){
                if(grid[r][c]=='1'){
                    islandNum++;
                    dfs(grid,{r,c});
                }
            }
        }
        return islandNum;
    }
};

const vector<pair<int, int>> Solution::dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int main() {
    std::vector<std::vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    Solution sol;
    int numberOfIslands = sol.numIslands(grid);

    std::cout << "Number of islands: " << numberOfIslands << std::endl;

    return 0;
}