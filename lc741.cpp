#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
private:
    vector<vector<vector<int>>> maxCherry;//k steps, player1_row,player_2
    const int NEG=-1000000;
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n=grid.size();
        maxCherry.resize(2*n-1,vector<vector<int>>(n,vector<int>(n,NEG)));
        maxCherry[0][0][0]=grid[0][0];
        for(int k=1;k<=2*(n-1);k++){
            for(int r1=max(0,k-(n-1));r1<= min(n-1,k);r1++){//k-(n-1) 我下的步數
                for(int r2=max(0,k-(n-1));r2<=min(n-1,k);r2++){
                    int c1=k-r1;
                    int c2=k-r2;
                    //擋 invalid ceil
                    if(grid[r1][c1]==-1 || grid[r2][c2]==-1) continue;
                    //calc best cherry pick so far at this step
                    int best=NEG;
                    //prev step + this step
                    //find the best prev cherry count
                    best=max(best,maxCherry[k-1][r1][r2]);
                    if(r1>0) best= max(best, maxCherry[k-1][r1-1][r2]);
                    if(r2>0) best= max(best,maxCherry[k-1][r1][r2-1]);
                    if(r1>0 && r2>0) best=max(best,maxCherry[k-1][r1-1][r2-1]);
                    if(best<0) continue;//no progress at this step
                    maxCherry[k][r1][r2]=best;
                    maxCherry[k][r1][r2]+=grid[r1][c1];
                    if(r1!=r2) maxCherry[k][r1][r2]+=grid[r2][c2];
                }
            }
        }
        return max(0,maxCherry[2*(n-1)][n-1][n-1]);
    }
};

int mainTest() {
    auto printCheck = [](string name, int got, int expected) {
        if (got == expected) {
            cout << "\033[1;32m"; // green
            cout << "[PASS] ";
        } else {
            cout << "\033[1;31m"; // red
            cout << "[FAIL] ";
        }
        cout << "\033[0m"; // reset
        cout << name
             << " | got = " << got
             << ", expected = " << expected
             << endl;
    };

    Solution sol;

    // ---------- Example 1 ----------
    vector<vector<int>> grid1 = {
            {0, 1, -1},
            {1, 0, -1},
            {1, 1,  1}
    };
    printCheck("Example 1", sol.cherryPickup(grid1), 5);
    // ---------- Example 2 ----------
    Solution sol2;
    vector<vector<int>> grid2 = {
            { 1,  1, -1},
            { 1, -1,  1},
            {-1,  1,  1}
    };
    printCheck("Example 2", sol2.cherryPickup(grid2), 0);

    return 0;
}