#include<bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
private:
    static constexpr size_t get_cell(size_t r,size_t c){
        return 3*(r/3)+c/3;
    }
    static constexpr size_t get_next_row(size_t r,size_t c){
        return r+(c+1)/9;
    }
    static constexpr size_t get_next_col(size_t c){
        return (c+1)%9;
    }
    static constexpr pair<size_t,size_t> get_next_empty_position(vector<vector<char>>& board,size_t r,size_t c){
        while(r!=9){
            if(board[r][c]=='.') return {r,c};
            //next row,next col
            r= get_next_row(r,c);
            c= get_next_col(c);
        }
        return {9,0};//end of traverse
    }
    static bool solve(vector<vector<char>>& board,
                      array<bitset<9>,9>& row_contains,
                      array<bitset<9>,9>& col_contains,
                      array<bitset<9>,9>& cell_contains,
                      size_t row_start,size_t col_start){
        //get next empty
        auto [r,c]= get_next_empty_position(board,row_start,col_start);
        //base case- return true/false
        if(r==9) return true;//traverse done!
        size_t cell= get_cell(r,c);
        bitset<9> contained_digit=row_contains[r]|col_contains[c]|cell_contains[cell];
        if(contained_digit.all()) return false;//we could not put ANY number but this position is remaining empty
        for(size_t digit_index=0;digit_index<9;++digit_index){
            if(contained_digit[digit_index]) continue;//ignore the digit used
            board[r][c]=static_cast<char>(digit_index+'1');
            row_contains[r].set(digit_index);
            col_contains[c].set(digit_index);
            size_t cell= get_cell(r,c);
            cell_contains[cell].set(digit_index);
            if(solve(board,row_contains,col_contains,cell_contains,r,c)) return true;
            //this number does not work out!
            row_contains[r].reset(digit_index);
            col_contains[c].reset(digit_index);
            cell_contains[cell].reset(digit_index);
        }
        //if all tried number do not work out
        board[r][c]='.';
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        array<bitset<9>,9> row_contains,col_contains,cell_contains;
        for(size_t r=0;r<9;++r){
            for(size_t c=0;c<9;++c){
                if(board[r][c]=='.') continue;
                char digit=board[r][c]-'1';//0-8
                row_contains[r].set(digit);
                col_contains[c].set(digit);
                size_t cell= get_cell(r,c);
                cell_contains[cell].set(digit);
            }
        }
        //solve
        solve(board,row_contains,col_contains,cell_contains,0,0);
    }
};

void printTestResult(int testNum, const vector<vector<char>>& expected, const vector<vector<char>>& actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: " << endl;
        for (const auto& row : expected) {
            for (char ch : row) {
                cout << ch << " ";
            }
            cout << endl;
        }
        cout << "Actual: " << endl;
        for (const auto& row : actual) {
            for (char ch : row) {
                cout << ch << " ";
            }
            cout << endl;
        }
        cout << endl;
        failedTests++;
    }
}

int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1
    {
        Solution sol;
        vector<vector<char>> board = {
                {'5','3','.','.','7','.','.','.','.'},
                {'6','.','.','1','9','5','.','.','.'},
                {'.','9','8','.','.','.','.','6','.'},
                {'8','.','.','.','6','.','.','.','3'},
                {'4','.','.','8','.','3','.','.','1'},
                {'7','.','.','.','2','.','.','.','6'},
                {'.','6','.','.','.','.','2','8','.'},
                {'.','.','.','4','1','9','.','.','5'},
                {'.','.','.','.','8','.','.','7','9'}
        };
        vector<vector<char>> expected = {
                {'5','3','4','6','7','8','9','1','2'},
                {'6','7','2','1','9','5','3','4','8'},
                {'1','9','8','3','4','2','5','6','7'},
                {'8','5','9','7','6','1','4','2','3'},
                {'4','2','6','8','5','3','7','9','1'},
                {'7','1','3','9','2','4','8','5','6'},
                {'9','6','1','5','3','7','2','8','4'},
                {'2','8','7','4','1','9','6','3','5'},
                {'3','4','5','2','8','6','1','7','9'}
        };
        sol.solveSudoku(board);
        printTestResult(++totalTests, expected, board, failedTests);
    }

    // Add more test cases here

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
