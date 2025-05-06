#include <bits/stdc++.h>
#define testMain main
using namespace std;

class NumMatrix {
private:
    vector<vector<int>> recSum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        // TODO: Precompute any data structures needed for O(1) queries.
        int M=matrix.size();
        int N=matrix[0].size();
        recSum.resize(M+1,vector<int>(N+1,0));
        for(int r=1;r<M+1;r++){
            for(int c=1;c<N+1;c++){
                recSum[r][c]=matrix[r-1][c-1]+recSum[r-1][c]+recSum[r][c-1]-recSum[r-1][c-1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        // TODO: Return the sum of the submatrix in O(1).
        //abcd=0d-0b-0c+0a
        int r1=row1+1;
        int r2=row2+1;
        int c1=col1+1;
        int c2=col2+1;
        return recSum[r2][c2]-recSum[r1-1][c2]-recSum[r2][c1-1]+recSum[r1-1][c1-1];
    }
};

// Helper function to run a test case with multiple queries
void runTest(int testNum,
             vector<vector<int>> matrix,
             vector<tuple<int,int,int,int,int>> queries) {
    NumMatrix obj(matrix);
    bool pass = true;
    for (auto &q : queries) {
        int row1, col1, row2, col2, expected;
        tie(row1, col1, row2, col2, expected) = q;
        int result = obj.sumRegion(row1, col1, row2, col2);
        if (result != expected) {
            pass = false;
            cout << "\033[1;31mTest Case " << testNum
                 << " Failed at query (" << row1 << "," << col1
                 << "," << row2 << "," << col2 << "): got "
                 << result << ", expected " << expected
                 << "\033[0m" << endl;
        }
    }
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    }
}

int testMain(){
    // Example 1
    vector<vector<int>> mat1 = {
            {3, 0, 1, 4, 2},
            {5, 6, 3, 2, 1},
            {1, 2, 0, 1, 5},
            {4, 1, 0, 1, 7},
            {1, 0, 3, 0, 5}
    };
    runTest(1, mat1, {
            make_tuple(2, 1, 4, 3, 8),
            make_tuple(1, 1, 2, 2, 11),
            make_tuple(1, 2, 2, 4, 12)
    });

    // Additional Test Case
    vector<vector<int>> mat2 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    runTest(2, mat2, {
            make_tuple(0, 0, 1, 1, 12),
            make_tuple(0, 1, 2, 2, 33)
    });

    return 0;
}