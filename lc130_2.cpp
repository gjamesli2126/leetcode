#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<vector<char>> board;
    int rmax,cmax;
    vector<pair<int,int>> dirs{
            {0,1},{1,0},{-1,0},{0,-1}
    };
    void dfs(int r,int c){
        if(r<0 || c<0 || r==rmax || c==cmax || board[r][c]!='O') return;
        board[r][c]='r';
        for(const auto& [dr,dc]:dirs){
            dfs(r+dr,c+dc);
        }
    }
public:
    void solve(vector<vector<char>>& board0) {
        board=std::move(board0);
        rmax=static_cast<int>(board.size());
        cmax=static_cast<int>(board[0].size());
        //loop thru borader to do DFS, mark it as remain

        //left most & right most
        for(int r=0;r!=rmax;++r){
            if(board[r][0]=='O') dfs(r,0);
            if(board[r][cmax-1]=='O') dfs(r,cmax-1);
        }
        //top & bottom
        for(int c=0;c!=cmax;++c){
            if(board[0][c]=='O') dfs(0,c);
            if(board[rmax-1][c]=='O') dfs(rmax-1,c);
        }

        //loop thru all, chanced non remain as 'X', and remain as 'O'
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                if(board[r][c]!='r') board[r][c]='X';
                else board[r][c]='O';
            }
        }
        board0=std::move(board);
    }
};

void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

bool compareBoards(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    if (a.size() != b.size() || (a.size() && a[0].size() != b[0].size())) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

void printTestResult(int testNum, const vector<vector<char>>& expected, const vector<vector<char>>& actual) {
    cout << "Test #" << testNum << ": ";
    if (compareBoards(expected, actual)) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
        cout << "Expected: " << endl;
        printBoard(expected);
        cout << "Actual: " << endl;
        printBoard(actual);
    }
    cout << endl;
}

int mainTest() {
    Solution sol;

    // Test 1
    vector<vector<char>> board1 = {
            {'X','X','X','X'},
            {'X','O','O','X'},
            {'X','X','O','X'},
            {'X','O','X','X'}
    };
    vector<vector<char>> expected1 = {
            {'X','X','X','X'},
            {'X','X','X','X'},
            {'X','X','X','X'},
            {'X','O','X','X'}
    };
    sol.solve(board1);
    printTestResult(1, expected1, board1);

    // Test 2
    vector<vector<char>> board2 = {{'X'}};
    vector<vector<char>> expected2 = {{'X'}};
    sol.solve(board2);
    printTestResult(2, expected2, board2);

    // Add more tests as needed

    return 0;
}
