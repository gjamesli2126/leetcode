#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
    unordered_map<char,int> cfmap;
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // each row
        for(const auto& row:board){
            for(const char& c:row){
                if(c=='.') continue;
                cfmap[c]++;
                if(cfmap[c]>1) return false;
            }
            cfmap.clear();
        }

        //each col
        for(int col=0;col<9;++col){
            for(int row=0;row<9;++row){
                char c=board[row][col];
                if(c=='.') continue;
                cfmap[c]++;
                if(cfmap[c]>1) return false;
            }
            cfmap.clear();
        }

        //each 9sqr
        for(int row=0;row<9;row+=3){
            for(int col=0;col<9;col+=3){
                for(int r=row;r<row+3;++r){
                    for(int c=col;c<col+3;++c){
                        char ch=board[r][c];
                        if(ch=='.') continue;
                        cfmap[ch]++;
                        if(cfmap[ch]>1) return false;
                    }
                }
                cfmap.clear();
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
