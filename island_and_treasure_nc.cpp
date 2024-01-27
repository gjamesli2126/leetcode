#include<bits/stdc++.h>
using namespace std;
#define mainTest main
constexpr int INF = 2147483647;

class Solution {
private:
    vector<vector<int>> grid;
    int rmax,cmax;
    vector<pair<int,int>> dirs{
            {0,1},{1,0},{0,-1},{-1,0}
    };
    void bfs(queue<pair<int,int>>& q){
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop();
            for(const auto& [dr,dc]:dirs){
                int r=dr+r0;
                int c=dc+c0;
                if(r<0 || c<0 || r==rmax || c==cmax || grid[r][c]!=INF) continue;
                q.emplace(r,c);
                grid[r][c]=grid[r0][c0]+1;
            }
        }
    }
public:
    void islandsAndTreasure(vector<vector<int>>& grid0) {
        grid=std::move(grid0);
        rmax=static_cast<int>(grid.size());
        cmax=static_cast<int>(grid[0].size());
        queue<pair<int,int>> q;
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(grid[r][c]==0) q.emplace(r,c);
            }
        }
        bfs(q);
        grid0=std::move(grid);
    }
};

void printTestResult(int testNum, const vector<vector<int>>& expected, vector<vector<int>>& actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    bool passed = true;
    for (size_t i = 0; i < expected.size() && passed; ++i) {
        for (size_t j = 0; j < expected[0].size() && passed; ++j) {
            if (expected[i][j] != actual[i][j]) {
                passed = false;
            }
        }
    }

    if (passed) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: ";
        for (const auto& row : expected) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        cout << "Actual: ";
        for (const auto& row : actual) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1
    {
        Solution sol;
        vector<vector<int>> grid = {
                {INF, -1, 0, INF},
                {INF, INF, INF, -1},
                {INF, -1, INF, -1},
                {0, -1, INF, INF}
        };
        vector<vector<int>> expected = {
                {3, -1, 0, 1},
                {2, 2, 1, -1},
                {1, -1, 2, -1},
                {0, -1, 3, 4}
        };
        sol.islandsAndTreasure(grid);
        printTestResult(++totalTests, expected, grid, failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<vector<int>> grid = {
                {0, -1},
                {INF, INF}
        };
        vector<vector<int>> expected = {
                {0, -1},
                {1, 2}
        };
        sol.islandsAndTreasure(grid);
        printTestResult(++totalTests, expected, grid, failedTests);
    }

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
