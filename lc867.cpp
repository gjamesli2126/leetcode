//#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        unsigned long r,c;
        if(matrix.size()==matrix[0].size()){
            for(r=0;r<matrix.size();++r){
                for(c=r+1;c<matrix.size();++c){
                    if(r==c) continue;
                    swap(matrix[r][c],matrix[c][r]);
                }
            }
            return matrix;
        }else{//diff dimension
            unsigned long orgRmax=matrix.size();
            unsigned long orgCmax=matrix[0].size();
            vector<vector<int>> transposed(orgCmax,vector<int>(orgRmax));
            for(r=0;r<orgCmax;++r){
                for(c=0;c<orgRmax;++c){
                    transposed[r][c]=matrix[c][r];
                }
            }
            return transposed;
        }
    }
};

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "[";
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (j > 0) cout << ",";
            cout << matrix[i][j];
        }
        cout << "]";
    }
    cout << "]";
}

int mainTest() {
    vector<pair<vector<vector<int>>, vector<vector<int>>>> testCases = {
            {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}}, // Example 1
            {{{1, 2, 3}, {4, 5, 6}}, {{1, 4}, {2, 5}, {3, 6}}},                     // Example 2
            {{{1}}, {{1}}},                                                        // Single element
            {{{1, 2}}, {{1}, {2}}}                                                 // Row to column
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        vector<vector<int>> inputMatrix = testCases[i].first;
        vector<vector<int>> expectedOutput = testCases[i].second;

        Solution solution; // Create a new object for each test case
        vector<vector<int>> actualOutput = solution.transpose(inputMatrix);

        cout << "Test " << i + 1 << ": ";
        if (actualOutput == expectedOutput) {
            cout << green << "PASS" << reset;
        } else {
            cout << red << "FAIL" << reset;
        }
        cout << " - Input: ";
        printMatrix(inputMatrix);
        cout << "; Expected: ";
        printMatrix(expectedOutput);
        cout << "; Actual: ";
        printMatrix(actualOutput);
        cout << endl;
    }

    return 0;
}