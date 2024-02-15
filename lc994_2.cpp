#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int rmax,cmax;
    vector<vector<int>> grid;
    vector<pair<int,int>> dirs{
            {0,1},{1,0},{-1,0},{0,-1}
    };
    queue<pair<int,int>> look;
    int fresh=0;
    int bfs(){
        int days=0;
        while(!look.empty() && fresh) {
            ++days;
            int n=static_cast<int>(look.size());
            while (n--) {
                auto [r0, c0] = look.front();
                look.pop();

                for (const auto &[dr, dc]: dirs) {
                    int r = r0 + dr, c = c0 + dc;
                    if (r < 0 || r == rmax || c < 0 || c == cmax || grid[r][c] != 1) continue;
                    look.emplace(r, c);
                    grid[r][c] = 2;
                    --fresh;
                }
            }
        }
        return days;
    }
public:
    int orangesRotting(vector<vector<int>>& grid0) {
        grid=std::move(grid0);
        rmax=static_cast<int>(grid.size());
        cmax=static_cast<int>(grid[0].size());
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(grid[r][c]==2) look.emplace(r,c);
                else if(grid[r][c]==1) ++fresh;
            }
        }
        if(!fresh) return 0;
        int days=bfs();
        return fresh?-1:days;
    }
};
void printTestResult(int testNum, int expected, int actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: " << expected << ", Actual: " << actual << endl;
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
        vector<vector<int>> grid = {{2,1,1}, {1,1,0}, {0,1,1}};
        int expected = 4;
        int actual = sol.orangesRotting(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<vector<int>> grid = {{2,1,1}, {0,1,1}, {1,0,1}};
        int expected = -1;
        int actual = sol.orangesRotting(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 3
    {
        Solution sol;
        vector<vector<int>> grid = {{0,2}};
        int expected = 0;
        int actual = sol.orangesRotting(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
    }
    // Test 4
    {
        Solution sol;
        vector<vector<int>> grid = {{0}};
        int expected = 0;
        int actual = sol.orangesRotting(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
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