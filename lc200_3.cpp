#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
private:
    int rmax,cmax;
    vector<pair<int,int>> dirs{
            {0,1},{1,0},{-1,0},{0,-1}
    };
    void dfs(vector<vector<char>>& grid,int r,int c){
        if(r<0 || r==rmax || c<0 || c==cmax || grid[r][c]=='0') return;
        grid[r][c]='0';
        for(const auto& [dr,dc]:dirs){
            dfs(grid,r+dr,c+dc);
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        rmax=static_cast<int>(grid.size());
        cmax=static_cast<int>(grid[0].size());
        int islandNum=0;
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(grid[r][c]=='0') continue;
                ++islandNum;
                dfs(grid,r,c);
            }
        }
        return islandNum;
    }
};
int mainTest() {
    vector<vector<vector<char>>> testCases = {
            {
                    {'1','1','1','1','0'},
                    {'1','1','0','1','0'},
                    {'1','1','0','0','0'},
                    {'0','0','0','0','0'}
            },
            {
                    {'1','1','0','0','0'},
                    {'1','1','0','0','0'},
                    {'0','0','1','0','0'},
                    {'0','0','0','1','1'}
            }
            // Add more test cases here
    };

    vector<int> expectedResults = {1, 3}; // Expected results for each test case

    int totalTests = static_cast<int>(testCases.size());
    int passedTests = 0;

    for (int i = 0; i < totalTests; ++i) {
        Solution sol;
        int result = sol.numIslands(testCases[i]);
        bool passed = result == expectedResults[i];

        // Print test case details
        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "Input: " << endl;
        for (const auto& row : testCases[i]) {
            for (const auto& cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << "Expected Output: " << expectedResults[i] << endl;
        cout << "My Output: " << result << endl;

        // Check and print test result
        if (passed) {
            cout << "\033[32mPass\033[0m" << endl; // Green color for pass
            ++passedTests;
        } else {
            cout << "\033[31mFail\033[0m" << endl; // Red color for fail
        }
        cout << endl;
    }

    // Print summary
    cout << "Passed " << passedTests << " out of " << totalTests << " tests." << endl;
    if (passedTests < totalTests) {
        cout << "\033[31mError Rate: " << (totalTests - passedTests) << "/" << totalTests << "\033[0m" << endl; // Red color for error rate if > 0
    } else {
        cout << "\033[32mError Rate: " << (totalTests - passedTests) << "/" << totalTests << "\033[0m" << endl; // Green color for error rate if 0
    }

    return 0;
}
