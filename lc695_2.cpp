#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<vector<int>> grid;
    int rmax,cmax,areaMax=0;
    vector<pair<int,int>> dirs{
            {0,1},{1,0},{-1,0},{0,-1}
    };
    void dfs(const int& r0,const int& c0,int& area){
        if(r0<0 || c0<0 || r0==rmax || c0==cmax || grid[r0][c0]==0) return;
        ++area;
        grid[r0][c0]=0;
        areaMax= max(areaMax,area);
        for(const auto& [dr,dc]:dirs){
            dfs(r0+dr,c0+dc,area);
        }
    }
public:

    int maxAreaOfIsland(vector<vector<int>>& grid0) {
        //by using dfs loop thru vec, market element as 0 means visited
        grid=std::move(grid0);
        rmax=static_cast<int>(grid.size());
        cmax=static_cast<int>(grid[0].size());

        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(grid[r][c]==0) continue;
                int area=0;
                dfs(r,c,area);
            }
        }
        return areaMax;
    }
};

void printTestResult(int testNum, int expected, int actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m" // Red for failed
             << ". Expected: " << expected << ", Actual: " << actual;
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    vector<pair<vector<vector<int>>, int>> tests = {
            {{{0,0,1,0,0,0,0,1,0,0,0,0,0},
                     {0,0,0,0,0,0,0,1,1,1,0,0,0},
                     {0,1,1,0,1,0,0,0,0,0,0,0,0},
                     {0,1,0,0,1,1,0,0,1,0,1,0,0},
                     {0,1,0,0,1,1,0,0,1,1,1,0,0},
                     {0,0,0,0,0,0,0,0,0,0,1,0,0},
                     {0,0,0,0,0,0,0,1,1,1,0,0,0},
                     {0,0,0,0,0,0,0,1,1,0,0,0,0}}, 6},
            {{{0,0,0,0,0,0,0,0}}, 0}
            // Add more test cases as needed
    };

    int failedTests = 0;
    int testNum = 0;

    for (auto& test : tests) {
        Solution sol;
        printTestResult(++testNum, test.second, sol.maxAreaOfIsland(test.first), failedTests);
    }

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / testNum;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
