#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int rmax,cmax;
    inline bool validRC(int r,int c){
        return r>=0 && c>=0 && r<rmax && c<cmax;
    }
public:
    void setZeroes(vector<vector<int>>& matrix) {
        //use the 0th row & 0th col as flag
        rmax=matrix.size();
        cmax=matrix[0].size();
        //給該 row0 & c0 定義是否要0
        //先run 完 要flag的地方因為有可能會增加需要0的地方
        //EDGES
        bool firstRowZeros= false,firstColZeros= false;
        for(int r=0;r<rmax;r++){
            if(matrix[r][0]!=0) continue;
            firstColZeros=true;
            break;
        }
        for(int c=0;c<cmax;c++){
            if(matrix[0][c]!=0) continue;
            firstRowZeros=true;
            break;
        }

        //BODY
        for(int r=1;r<rmax;r++){
            for(int c=1;c<cmax;c++){
                if(matrix[r][c]!=0) continue;
                matrix[r][0]=0;
                matrix[0][c]=0;
            }
        }
        //make flag effective
        //check row==0->
        for(int c=1;c<cmax;c++){
            if(matrix[0][c]!=0) continue;
            for(int r=1;r<rmax;r++) matrix[r][c]=0;
        }
        //check col==0->>
        for(int r=1;r<rmax;r++){
            if(matrix[r][0]!=0) continue;
            for(int c=1;c<cmax;c++) matrix[r][c]=0;
        }
        // do not start from r=0 & c=0 becasue it may affect the flag
        if(firstRowZeros) for(int c=0;c<cmax;c++) matrix[0][c]=0;
        if(firstColZeros) for(int r=0;r<rmax;r++) matrix[r][0]=0;
    }
};

void printMatrix(const vector<vector<int>>& mat) {
    cout << "[\n";
    for (const auto& row : mat) {
        cout << "  [";
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j] << (j + 1 < row.size() ? ", " : "");
        }
        cout << "]\n";
    }
    cout << "]";
}

bool matricesEqual(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void runTest(int testNum,
             vector<vector<int>> matrix,
             const vector<vector<int>>& expected)
{
    Solution sol;
    sol.setZeroes(matrix);
    bool pass = matricesEqual(matrix, expected);
    if (pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed.\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed.\n  Got:\n";
        printMatrix(matrix);
        cout << "\n  Expected:\n";
        printMatrix(expected);
        cout << "\033[0m\n";
    }
}

int testMain() {
    // Example 1
    runTest(1,
            {{1,1,1},
             {1,0,1},
             {1,1,1}},
            {{1,0,1},
             {0,0,0},
             {1,0,1}}
    );

    // Example 2
    runTest(2,
            {{0,1,2,0},
             {3,4,5,2},
             {1,3,1,5}},
            {{0,0,0,0},
             {0,4,5,0},
             {0,3,1,0}}
    );

    // Additional tests
    // Single row
    runTest(3,
            {{1,0,3,4}},
            {{0,0,0,0}}
    );
    // Single column
    runTest(4,
            {{1},{0},{3}},
            {{0},{0},{0}}
    );
    // No zeros
    runTest(5,
            {{1,2,3},{4,5,6}},
            {{1,2,3},{4,5,6}}
    );

    return 0;
}