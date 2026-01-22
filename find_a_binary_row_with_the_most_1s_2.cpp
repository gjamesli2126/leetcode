#include <bits/stdc++.h>
#include <chrono>
#include <thread>
#include <iomanip>

#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION (To Implement)
// ==========================================
class Solution {
public:
    /**
     * Finds the row with the maximum number of 1s.
     * Constraint: The algorithm should be O(N + M).
     * * @param mat A binary matrix where each row is sorted (0s then 1s).
     * @return vector<int> {rowIndex, count}. Return {-1, 0} if no 1s found.
     */
    vector<int> rowWithMax1s(vector<vector<int>>& mat) {
        int r_max=mat.size()-1;
        int c_max=mat[0].size()-1;
        int c=c_max;
        int ans_r=-1;//init with corner case
        for(int r=0;r<=r_max;r++){
            int c0=c;
            while(c>=0 && mat[r][c]==1) --c;
            if(c0-c>0) ans_r=r;
        }
        return vector<int>{ans_r,c_max-c};
    }
};

// ==========================================
//  REFERENCE SOLUTION (Brute Force O(N*M))
// ==========================================
// This is used as "Ground Truth" to verify your optimized solution.
class BruteForce {
public:
    vector<int> solve(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return {-1, 0};
        int bestRow = -1;
        int maxCount = -1;

        // Simple iteration through every cell
        for(int i = 0; i < mat.size(); i++) {
            int count = 0;
            for(int j = 0; j < mat[i].size(); j++) {
                if(mat[i][j] == 1) count++;
            }
            // Strict inequality usually finds the first row with max
            if (count > maxCount) {
                maxCount = count;
                bestRow = i;
            }
        }

        if (maxCount == 0) return {-1, 0};
        return {bestRow, maxCount};
    }
};

// ==========================================
//  TEST HELPERS
// ==========================================

// Helper to pretty print matrix (small ones only)
void printMatrix(const vector<vector<int>>& mat) {
    if(mat.size() > 10) { cout << "   [Large Matrix...]" << endl; return; }
    for(auto& row : mat) {
        cout << "   [ ";
        for(int x : row) cout << x << " ";
        cout << "]" << endl;
    }
}

// Generate Random Sorted Binary Matrix
// Key constraint: Rows must be sorted (0s followed by 1s)
vector<vector<int>> generateSortedMatrix(int rows, int cols) {
    vector<vector<int>> mat(rows, vector<int>(cols, 0));
    for(int i = 0; i < rows; i++) {
        // Randomly decide how many 1s are in this row
        // 0 to cols
        int onesCount = rand() % (cols + 1);
        int startIdx = cols - onesCount;

        for(int j = startIdx; j < cols; j++) {
            mat[i][j] = 1;
        }
    }
    return mat;
}

void printProgressBar(int current, int total) {
    int barWidth = 40;
    float progress = (float)current / total;
    cout << "\rProgress: [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %";
    cout.flush();
}

// ==========================================
//  MAIN DRIVER
// ==========================================
int mainTest() {
    srand(time(0));
    Solution sol;
    BruteForce bf;
    int testNum = 0;
    int failedTests = 0;

    cout << "=== MANUAL CASES ===" << endl;

    // Case 1: Example from Image
    // 0, 1, 1, 1, 1 (4 ones)
    // 0, 0, 1, 1, 1 (3 ones)
    // 1, 1, 1, 1, 1 (5 ones) -> Target
    // 0, 0, 0, 0, 0 (0 ones)
    vector<vector<int>> t1 = {
            {0, 1, 1, 1, 1},
            {0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0}
    };

    // We expect Row 2 with 5 ones
    vector<int> res1 = sol.rowWithMax1s(t1);
    cout << "Test #" << ++testNum << " (Image Example): ";
    if(res1[0] == 2 && res1[1] == 5) cout << "\033[32m[PASS]\033[0m" << endl;
    else {
        cout << "\033[31m[FAIL]\033[0m Exp: {2, 5}, Got: {" << res1[0] << ", " << res1[1] << "}" << endl;
        failedTests++;
    }

    // Case 2: All Zeros
    vector<vector<int>> t2 = {{0,0}, {0,0}};
    vector<int> res2 = sol.rowWithMax1s(t2);
    cout << "Test #" << ++testNum << " (All Zeros): ";
    if(res2[0] == -1) cout << "\033[32m[PASS]\033[0m" << endl;
    else { cout << "\033[31m[FAIL]\033[0m Got: {" << res2[0] << ", " << res2[1] << "}" << endl; failedTests++; }

    // Case 3: All Ones
    vector<vector<int>> t3 = {{1,1}, {1,1}};
    vector<int> res3 = sol.rowWithMax1s(t3);
    cout << "Test #" << ++testNum << " (All Ones): ";
    // Assuming we want the FIRST row with max ones
    if(res3[0] == 0 && res3[1] == 2) cout << "\033[32m[PASS]\033[0m" << endl;
    else { cout << "\033[31m[FAIL]\033[0m Got: {" << res3[0] << ", " << res3[1] << "}" << endl; failedTests++; }


    cout << endl << "=== STRESS TEST (Optimized vs Brute Force) ===" << endl;

    int stressCount = 2000;
    int passedStress = 0;

    for(int i=0; i<stressCount; i++) {
        int r = 1 + rand() % 50; // Random rows 1-50
        int c = 1 + rand() % 50; // Random cols 1-50
        vector<vector<int>> mat = generateSortedMatrix(r, c);

        vector<int> expected = bf.solve(mat);
        vector<int> actual = sol.rowWithMax1s(mat);

        // Verification Logic:
        // 1. If both return {-1, 0} (No ones found) -> Pass
        // 2. If counts match (actual[1] == expected[1]) -> Pass
        //    (We allow different row indexes if multiple rows have the same max count,
        //     though usually we want the smallest index. If your logic is stable,
        //     it should match the brute force index too).

        bool pass = false;
        if (expected[0] == -1 && actual[0] == -1) pass = true;
        else if (expected[1] == actual[1]) pass = true; // Checking count only for lenient test

        if(pass) {
            passedStress++;
        } else {
            cout << "\n\033[31mStress Fail!\033[0m" << endl;
            cout << "Dims: " << r << "x" << c << endl;
            // printMatrix(mat); // Uncomment to debug
            cout << "Exp: Row " << expected[0] << " (Cnt " << expected[1] << ")" << endl;
            cout << "Got: Row " << actual[0] << " (Cnt " << actual[1] << ")" << endl;
            failedTests++;
            break;
        }

        if (i % 20 == 0) printProgressBar(i, stressCount);
    }
    printProgressBar(stressCount, stressCount);

    cout << endl << endl << "==========================================" << endl;
    if(failedTests == 0) cout << "\033[32mAll Tests Passed (100%)\033[0m" << endl;
    else cout << "\033[31mTests Failed: " << failedTests << "\033[0m" << endl;
    cout << "==========================================" << endl;

    return 0;
}