#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// Macro to avoid main function conflict
#define mainTest main

using namespace std;

// ==========================================
// YOUR SOLUTION CLASS (Optimal O(N+M))
// ==========================================
class Solution {
public:
    // Returns {rowIndex, numberOfOnes}
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        //階梯算法
        int max_r=mat.size()-1;
        int max_c=mat[0].size()-1;
        int max_1s=0;
        int win_row=0;
        int col=max_c;
        for(int row=0;row<=max_r;row++){
            if(col>=0 && mat[row][col]==0) continue;
            while(col>=0 && mat[row][col]==1){
                --col;
                max_1s++;
                win_row=row;
            }
        }
        return {win_row,max_1s};
    }
};

// ==========================================
// TEST HARNESS UTILITIES
// ==========================================

// Oracle: Brute Force O(N*M)
// Since rows are sorted, we could use Binary Search O(N log M), 
// but straight counting is safer as a ground truth.
vector<int> solveBruteForce(const vector<vector<int>>& mat) {
    int maxOnes = -1;
    int bestRow = 0;

    for (int i = 0; i < mat.size(); i++) {
        int count = 0;
        for (int val : mat[i]) {
            count += val;
        }

        // Tie-breaking: strict greater checks ensure we keep the smallest index
        if (count > maxOnes) {
            maxOnes = count;
            bestRow = i;
        }
    }
    return {bestRow, maxOnes};
}

// Helper: Generate a "Sorted" Binary Matrix
// Valid row: 0,0,0,1,1 (Ok) | 1,1,1 (Ok) | 0,0,0 (Ok)
// Invalid row: 0,1,0,1 (Bad)
vector<vector<int>> generateSortedMatrix(int rows, int cols) {
    vector<vector<int>> mat(rows, vector<int>(cols));
    for(int i=0; i<rows; ++i) {
        // Decide how many 1s this row has (0 to cols)
        int numOnes = rand() % (cols + 1);
        int numZeros = cols - numOnes;

        // Fill 0s first, then 1s
        for(int j=0; j<cols; ++j) {
            if (j < numZeros) mat[i][j] = 0;
            else mat[i][j] = 1;
        }
    }
    return mat;
}

void runTest(int testId, vector<vector<int>>& mat, int& failedTests) {
    Solution sol;

    vector<int> expected = solveBruteForce(mat);
    vector<int> actual = sol.rowAndMaximumOnes(mat);

    cout << "Test #" << testId << ": ";

    // Compare Index and Count
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m";
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m";
        cout << " | Expected: [" << expected[0] << ", " << expected[1] << "]";
        cout << ", Actual: [" << actual[0] << ", " << actual[1] << "]";

        if (mat.size() <= 10 && mat[0].size() <= 10) {
            cout << "\nInput Matrix:\n";
            for(auto& row : mat) {
                cout << "  [";
                for(int x : row) cout << x << ",";
                cout << "]\n";
            }
        }
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Manual Edge Cases ===" << endl;

    // Test 1: Example from your screenshot
    // 0,1,1,1
    // 0,0,1,1
    // 1,1,1,1 (Best)
    // 0,0,0,0
    {
        vector<vector<int>> mat = {
                {0,1,1,1},
                {0,0,1,1},
                {1,1,1,1},
                {0,0,0,0}
        };
        runTest(++totalTests, mat, failedTests);
    }

    // Test 2: Tie Breaking (Should return index 0)
    // 0,1
    // 0,1
    {
        vector<vector<int>> mat = {{0,1}, {0,1}};
        runTest(++totalTests, mat, failedTests);
    }

    // Test 3: All Zeros
    {
        vector<vector<int>> mat = {{0,0,0}, {0,0,0}};
        runTest(++totalTests, mat, failedTests);
    }

    // Test 4: All Ones
    {
        vector<vector<int>> mat = {{1,1}, {1,1}};
        runTest(++totalTests, mat, failedTests);
    }

    // Test 5: Single element 1
    {
        vector<vector<int>> mat = {{1}};
        runTest(++totalTests, mat, failedTests);
    }

    // Test 6: Single element 0
    {
        vector<vector<int>> mat = {{0}};
        runTest(++totalTests, mat, failedTests);
    }

    cout << "\n=== Randomized Stress Tests ===" << endl;

    for (int i = 0; i < 100; i++) {
        // Generate random dimensions (1 to 50)
        int rows = (rand() % 50) + 1;
        int cols = (rand() % 50) + 1;

        vector<vector<int>> mat = generateSortedMatrix(rows, cols);
        runTest(++totalTests, mat, failedTests);
    }

    // ==========================================
    // REPORT
    // ==========================================
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m";
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m";
    }
    cout << endl;

    return 0;
}