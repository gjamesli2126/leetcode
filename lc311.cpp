#include <bits/stdc++.h>
#define testMain main
using namespace std;
class SparseMatrixCSR{
public:
    int row,col;
    vector<int> values,colIdx,rowStart;
    SparseMatrixCSR(const vector<vector<int>>& mat){
        row=mat.size();
        col=mat[0].size();
        rowStart.push_back(0);
        for(int r=0;r<row;r++){
            for(int c=0;c<col;c++){
                if(!mat[r][c]) continue;
                values.push_back(mat[r][c]);
                colIdx.push_back(c);
            }
            rowStart.push_back(values.size());
        }
    }
};
class SparseMatrixCSC{
public:
    int row,col;
    vector<int> values,rowIdx,colStart;
    SparseMatrixCSC(const vector<vector<int>>& mat){
        row=mat.size();
        col=mat[0].size();
        colStart.push_back(0);
        for(int c=0;c<col;c++){
            for(int r=0;r<row;r++){
                if(!mat[r][c]) continue;
                values.push_back(mat[r][c]);
                rowIdx.push_back(r);
            }
            colStart.push_back(values.size());
        }
    }
};
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        SparseMatrixCSR csr(mat1);
        SparseMatrixCSC csc(mat2);
        int amax=mat1.size();
        int bmax=mat2[0].size();
        vector<vector<int>> ans(amax,vector<int>(bmax));
        for(int a=0;a<amax;a++){
            for(int b=0;b<bmax;b++){
                int p=csr.rowStart[a];
                int p_end=csr.rowStart[a+1];
                int q=csc.colStart[b];
                int q_end=csc.colStart[b+1];
                while(p<p_end && q<q_end){
                    int colA=csr.colIdx[p];
                    int rowB=csc.rowIdx[q];
                    if(colA==rowB){
                        ans[a][b]+=csr.values[p++]*csc.values[q++];
                    }
                    else if(colA<rowB) p++;
                    else q++;
                }
            }
        }
        return  ans;
    }
};

// Helper to compare two matrices for equality.
bool equalMatrix(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Helper to print a matrix.
void printMatrix(const vector<vector<int>>& mat) {
    cout << "[";
    for (size_t i = 0; i < mat.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < mat[i].size(); ++j) {
            cout << mat[i][j] << (j + 1 < mat[i].size() ? ", " : "");
        }
        cout << "]" << (i + 1 < mat.size() ? ", " : "");
    }
    cout << "]";
}

// Helper function to run a test case.
void runTest(int testNum,
             vector<vector<int>> mat1,
             vector<vector<int>> mat2,
             vector<vector<int>> expected) {
    Solution sol;
    auto result = sol.multiply(mat1, mat2);
    if (equalMatrix(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m\n";
        cout << "Expected: ";
        printMatrix(expected);
        cout << "\nGot:      ";
        printMatrix(result);
        cout << "\n";
    }
}

int testMain(){
    // Example 1:
    // mat1 = [[1,0,0],[-1,0,3]]
    // mat2 = [[7,0,0],[0,0,0],[0,0,1]]
    // Output = [[7,0,0],[-7,0,3]]
    runTest(1,
            {{1,0,0},{-1,0,3}},
            {{7,0,0},{0,0,0},{0,0,1}},
            {{7,0,0},{-7,0,3}}
    );

    // Example 2:
    // mat1 = [[0]], mat2 = [[0]]
    // Output = [[0]]
    runTest(2,
            {{0}},
            {{0}},
            {{0}}
    );

    return 0;
}