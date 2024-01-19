#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int rmax,cmax;
    const vector<pair<int,int>> dirs{
            {1,0},{-1,0},{0,1},{0,-1}
    };
    queue<pair<int,int>> q;
    void bfsFindPath(vector<vector<int>>& mat){
//        vector<vector<bool>> visited(rmax,vector<bool>(cmax));
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop();
//            visited[r0][c0]=true;
            for(const auto& [dr,dc]:dirs){
                int r=dr+r0;
                int c=dc+c0;
                if(r<0 || c<0 || r==rmax || c==cmax || mat[r][c]==0 || mat[r][c]!=INT_MAX) continue;
                mat[r][c]=1+mat[r0][c0];
                q.push({r,c});
            }
        }
    }
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        rmax=mat.size();
        cmax=mat[0].size();
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(mat[r][c]==0) q.push({r,c});
                else mat[r][c]=INT_MAX;
            }
        }
        bfsFindPath(mat);
        return mat;
    }
};

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

bool compareMatrices(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

int mainTest() {
    vector<pair<vector<vector<int>>, vector<vector<int>>>> testCases = {
            {{{0,0,0},{0,1,0},{0,0,0}}, {{0,0,0},{0,1,0},{0,0,0}}}, // Test case 1 with expected result
            {{{0,0,0},{0,1,0},{1,1,1}}, {{0,0,0},{0,1,0},{1,2,1}}},  // Test case 2 with expected result
            {{{0},{0},{0},{0},{0}},{{0},{0},{0},{0},{0}}},
    };

    for (auto& [testCase, expectedResult] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input:" << endl;
        printMatrix(testCase);
        vector<vector<int>> result = solution.updateMatrix(testCase);
        cout << "Output:" << endl;
        printMatrix(result);

        bool isPass = compareMatrices(result, expectedResult);
        if (isPass) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
