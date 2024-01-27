#include<bits/stdc++.h>
using namespace std;
#define mainTest main

// Assuming you have the Solution class and pacificAtlantic method defined elsewhere

class Solution {
private:
    enum oceanReach{
        unknown,
        Pasicifc,
        atlanta,
        both
    };
    vector<vector<int>> heights;
    vector<vector<oceanReach>> status;
    int rmax,cmax;

    vector<pair<int,int>> dirs{
            {0,1},{1,0},{-1,0},{0,-1}
    };
    void bfs(int r00,int c00,oceanReach target){
        deque<pair<int,int>> dq{{r00,c00}};
        if(status[r00][c00]==unknown) status[r00][c00]=target;
        else if(status[r00][c00]!=target) status[r00][c00]=both;

        while(!dq.empty()){
            auto [r0,c0]=dq.front();
            dq.pop_front();
            for(const auto& [dr,dc]:dirs){
                int r=r0+dr,c=c0+dc;
                if(r<0 || c<0 || r==rmax || c==cmax) continue;
                if(status[r][c]==target || status[r][c]==both) continue;//meaning visited
                if(heights[r][c]<heights[r0][c0]) continue;//not possible
                dq.emplace_back(r,c);
                if(status[r][c]==unknown) status[r][c]=target;
                else if(status[r][c]!=target) status[r][c]=both;
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights0) {
        heights=std::move(heights0);
        rmax=static_cast<int>(heights.size());
        cmax=static_cast<int>(heights[0].size());
        if(rmax==1 && cmax==1) return {{0,0}};
        status.resize(rmax,vector<oceanReach>(cmax,unknown));

        //left-pac & right-atlanta
        for(int r=0;r!=rmax;++r) {
            bfs(r,0,oceanReach::Pasicifc);
            bfs(r,cmax-1,oceanReach::atlanta);
        }

        //up-pac & down-atlanta
        for(int c=0;c!=cmax;++c){
            bfs(0,c,oceanReach::Pasicifc);
            bfs(rmax-1,c,oceanReach::atlanta);
        }
        vector<vector<int>> result;
        for(int r=0;r!=rmax;++r){
            for(int c=0;c!=cmax;++c){
                if(status[r][c]==both) result.push_back({r,c});
            }
        }
        return result;
    }
};

void printTestResult(int testNum, const vector<vector<int>>& expected, const vector<vector<int>>& actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: ";
        for (const auto& pair : expected) {
            cout << "[" << pair[0] << "," << pair[1] << "] ";
        }
        cout << ", Actual: ";
        for (const auto& pair : actual) {
            cout << "[" << pair[0] << "," << pair[1] << "] ";
        }
        cout << endl;
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
        vector<vector<int>> heights = {
                {1,2,2,3,5},
                {3,2,3,4,4},
                {2,4,5,3,1},
                {6,7,1,4,5},
                {5,1,1,2,4}
        };
        vector<vector<int>> expected = {{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0}};
        printTestResult(++totalTests, expected, sol.pacificAtlantic(heights), failedTests);
    }

    // Test 2
    {
        Solution sol;
        vector<vector<int>> heights = {{1}};
        vector<vector<int>> expected = {{0,0}};
        printTestResult(++totalTests, expected, sol.pacificAtlantic(heights), failedTests);
    }

    // Add more tests here

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
