#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution{
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix){
        size_t rmax=matrix.size();
        size_t cmax=matrix[0].size();
        vector<vector<int>> transPosed(cmax,vector<int>(rmax,0));
        for(int r=0;r<rmax;r++){
            for(int c=0;c<cmax;c++){
                transPosed[c][r]=matrix[r][c];
            }
        }
        return transPosed;
    }
};

void printMatrix(const vector<vector<int>>& result, const vector<vector<int>>& expected){
    if (result == expected){
        cout << "\033[1;32mPass\033[0m Expected: ";
    }
    else{
        cout << "\033[1;31mFail\033[0m Expected: ";
    }

    cout << "[";
    for (size_t i = 0; i < expected.size(); ++i){
        if (i) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < expected[i].size(); ++j){
            if (j) cout << ",";
            cout << expected[i][j];
        }
        cout << "]";
    }
    cout << "] Got: [";
    for (size_t i = 0; i < result.size(); ++i){
        if (i) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j){
            if (j) cout << ",";
            cout << result[i][j];
        }
        cout << "]";
    }
    cout << "]" << endl;
}

int mainTest(){
    Solution sol;

    cout << "Test 1" << endl;
    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> expected1 = {{1,4,7},{2,5,8},{3,6,9}};
    printMatrix(sol.transpose(matrix1), expected1);

    cout << "Test 2" << endl;
    vector<vector<int>> matrix2 = {{1,2,3},{4,5,6}};
    vector<vector<int>> expected2 = {{1,4},{2,5},{3,6}};
    printMatrix(sol.transpose(matrix2), expected2);

    cout << "Test 3" << endl;
    vector<vector<int>> matrix3 = {{5}};
    vector<vector<int>> expected3 = {{5}};
    printMatrix(sol.transpose(matrix3), expected3);

    cout << "Test 4" << endl;
    vector<vector<int>> matrix4 = {{1,2},{3,4},{5,6}};
    vector<vector<int>> expected4 = {{1,3,5},{2,4,6}};
    printMatrix(sol.transpose(matrix4), expected4);

    return 0;
}