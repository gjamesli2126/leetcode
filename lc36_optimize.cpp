#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
    array<unordered_set<char>,9> rowSets,colSets,sqrSets;
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int row=0;row<9;++row){
            for(int col=0;col<9;++col){
                char c=board[row][col];
                if(c=='.') continue;
                if(rowSets[col].contains(c) || colSets[row].contains(c) || sqrSets[col/3+3*(row/3)].contains(c)) return false;
                rowSets[col].insert(c);
                colSets[row].insert(c);
                sqrSets[col/3+3*(row/3)].insert(c);
            }
        }
        return true;
    }
};

int mainTest() {
    // Create an instance of the Solution class
    Solution solution;

    // Define a series of test cases
    vector<pair<vector<vector<char>>, bool>> testCases = {
            {{{'5','3','.','.','7','.','.','.','.'},
                     {'6','.','.','1','9','5','.','.','.'},
                     {'.','9','8','.','.','.','.','6','.'},
                     {'8','.','.','.','6','.','.','.','3'},
                     {'4','.','.','8','.','3','.','.','1'},
                     {'7','.','.','.','2','.','.','.','6'},
                     {'.','6','.','.','.','.','2','8','.'},
                     {'.','.','.','4','1','9','.','.','5'},
                     {'.','.','.','.','8','.','.','7','9'}}, true},  // Example 1
            {{{'8','3','.','.','7','.','.','.','.'},
                     {'6','.','.','1','9','5','.','.','.'},
                     {'.','9','8','.','.','.','.','6','.'},
                     {'8','.','.','.','6','.','.','.','3'},
                     {'4','.','.','8','.','3','.','.','1'},
                     {'7','.','.','.','2','.','.','.','6'},
                     {'.','6','.','.','.','.','2','8','.'},
                     {'.','.','.','4','1','9','.','.','5'},
                     {'.','.','.','.','8','.','.','7','9'}}, false}   // Example 2
            // Add more test cases as needed
    };

    // Iterate through each test case
    for (int i = 0; i < testCases.size(); ++i) {
        // Retrieve the actual output from the isValidSudoku method
        bool actualOutput = solution.isValidSudoku(testCases[i].first);

        // Determine if the test case passed or failed
        bool status = (actualOutput == testCases[i].second);

        // Print the test results
        cout << "Test " << i + 1 << ": ";
        cout << "Input: board = \n[";
        for (const auto &row : testCases[i].first) {
            cout << "[";
            for (size_t j = 0; j < row.size(); ++j) {
                cout << "'" << row[j] << "'" << (j < row.size() - 1 ? ", " : "");
            }
            cout << "]" << (&row != &testCases[i].first.back() ? ",\n" : "");
        }
        cout << "];\n";
        cout << "Expected: " << (testCases[i].second ? "true" : "false");
        cout << ", Actual: " << (actualOutput ? "true" : "false");
        cout << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }

    return 0;
}
