#include<bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
private:
    static constexpr size_t get_cell(size_t row,size_t col) noexcept{
        return 3*(row/3)+col/3;
    }
    static constexpr size_t get_next_row(size_t row,size_t col) noexcept{
        return row+(col+1)/9;
    }
    static constexpr size_t get_next_col(size_t col) noexcept{
        return (col+1)%9;
    }
    static constexpr pair<size_t,size_t> get_next_empty_position(vector<vector<char>>& board,size_t row,size_t col) noexcept{
        while(row!=9){
            if(board[row][col]=='.') return {row,col};
            row= get_next_row(row,col);
            col= get_next_col(col);
        }
        return {9,0};
    }
    static bool solve(vector<vector<char>>& board, array<bitset<9>,9>& row_contains,array<bitset<9>,9>& col_contains,array<bitset<9>,9>& cell_contains, int row_start,int col_start) noexcept{
        auto [r0,c0]= get_next_empty_position(board,row_start,col_start);
        if(r0==9) return true;//end of board
        const bitset<9> contains=row_contains[r0]|col_contains[c0]|cell_contains[get_cell(r0,c0)];
        if(contains.all()) return false;
        for(size_t dig_index=0;dig_index<9;++dig_index){//guessing num: 1-9
            if(contains[dig_index]) continue;
            board[r0][c0]=static_cast<char>(dig_index+'1');
            row_contains[r0].set(dig_index);
            col_contains[c0].set(dig_index);
            size_t cell= get_cell(r0,c0);
            cell_contains[cell].set(dig_index);
            if(solve(board,row_contains,col_contains,cell_contains,r0,c0)) return true;
            row_contains[r0].reset(dig_index);
            col_contains[c0].reset(dig_index);
            cell_contains[cell].reset(dig_index);
        }
        board[r0][c0]='.';
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        array<bitset<9>,9> row_contains,col_contains,cell_contains;//default to zeros
        for(size_t r=0;r<9;++r){
            for(size_t c=0;c<9;++c){
                char digit=board[r][c];
                if(digit=='.') continue;
                size_t digit_index=digit-'1';
                row_contains[r].set(digit_index);
                col_contains[c].set(digit_index);
                cell_contains[get_cell(r,c)].set(digit_index);
            }
        }
        solve(board,row_contains,col_contains, cell_contains,0,0);
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
