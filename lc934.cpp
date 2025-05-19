#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int n;
    vector<int> dirs{1,0,-1,0,1};
    inline bool validRC(int r,int c){
        return r>=0 && c>=0 && r<n && c<n;
    }
    void dfsSetID2(vector<vector<int>>& g,int r,int c){
        g[r][c]=2;
        for(int i=0;i<4;i++){
            int newr=r+dirs[i];
            int newc=c+dirs[i+1];
            if(!validRC(newr,newc) || g[newr][newc]!=1) continue;
            dfsSetID2(g,newr,newc);
        }
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {
        // DFS to set the first island as ID2, the remaining 1 is the ID1 O(N)
        //then use BFS for all ID2 or ID1 to serach for shortest path O(N^2). N=n*n
        n= grid.size();
        if(n==2) return 1;
        //ID2 the first found island
        bool done=false;
        for(int r=0;r<n && !done;r++){
            for(int c=0;c<n;c++){
                if(!grid[r][c]) continue;
                dfsSetID2(grid,r,c);
                done=true;
                break;
            }
        }
        //iterate thru ID2's island and find the min distance w/ island, problably find the one with water conencted
        //queue up all possible starting point
        queue<pair<int,int>> q;//r,c
        for(int r=0;r<n;r++){
            for(int c=0;c<n;c++){
                if(grid[r][c]==2) q.emplace(r,c);
            }
        }
        //use BFS for dist
        int dist=0;
        while(!q.empty()){
            int qsz=q.size();
            while(qsz--){
                auto [r,c]=q.front();
                q.pop();
                for(int i=0;i<4;i++){
                    int newr=r+dirs[i];
                    int newc=c+dirs[i+1];
                    if(!validRC(newr,newc) || grid[newr][newc]==-1 || grid[newr][newc]==2) continue;
                    if(grid[newr][newc]==1) return dist;
                    grid[newr][newc]=-1;
                    q.emplace(newr,newc);
                }
            }
            dist++;//???
        }

        return 87426;
    }
};

void printGrid(const vector<vector<int>>& grid) {
    cout << "[\n";
    for (const auto& row : grid) {
        cout << "  [";
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j] << (j + 1 < row.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]";
}

void runTest(int testNum, vector<vector<int>> grid, int expected) {
    Solution sol;
    int result = sol.shortestBridge(grid);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: shortestBridge(grid) = " << result
             << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: shortestBridge(grid) = " << result
             << ", expected " << expected << "\nGrid was:\n";
        printGrid(grid);
        cout << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    runTest(1,
            {{0,1},
             {1,0}},
            1
    );
    // Example 2
    runTest(2,
            {{0,1,0},
             {0,0,0},
             {0,0,1}},
            2
    );
    // Example 3
    runTest(3,
            {{1,1,1,1,1},
             {1,0,0,0,1},
             {1,0,1,0,1},
             {1,0,0,0,1},
             {1,1,1,1,1}},
            1
    );
    // Additional test: minimal size
    runTest(4,
            {{1,0},
             {0,1}},
            1
    );
    return 0;
}