#include<bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
private:
    int rmax=3,cmax=3;
    vector<vector<int>> grid;
    int minSteps=9*9;
    void dfs(int pos,int steps){//position: 0~8
        if(pos==9) {
            minSteps = min(minSteps, steps);
            return;
        }
        if(grid[pos/3][pos%3]==0){
            int r0=pos/3,c0=pos%3;
            for(int p=0;p<9;++p){
                int r=p/3,c=p%3;
                if(grid[r][c]>1){
                    ++grid[r0][c0];
                    --grid[r][c];
                    dfs(pos+1,steps+abs(r-r0)+abs(c-c0));
                    --grid[r0][c0];
                    ++grid[r][c];
                }
            }
        }
        else{
            dfs(pos+1,steps);
        }

    }
public:
    int minimumMoves(vector<vector<int>>& grid0) {
        grid=std::move(grid0);
        dfs(0,0);//only keep moving to the right hesse 前者0不會倍更動，會有cell保留 >1

        return minSteps;
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
        vector<vector<int>> grid = {{1,1,0},{1,1,1},{1,2,1}};
        int expected = 3;
        int actual = sol.minimumMoves(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<vector<int>> grid = {{1,3,0},{1,0,0},{1,0,3}};
        int expected = 4;
        int actual = sol.minimumMoves(grid);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Add more test cases here

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
