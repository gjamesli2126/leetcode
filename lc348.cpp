//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
#define mainTest main

class TicTacToe {
private:
    vector<vector<int>> board;
    vector<vector<int>> counter;
    int n;
public:
    TicTacToe(int n0) {
        n=n0;
        board.resize(n,vector<int>(n,0));
        counter.resize(2,vector<int>(2*n+2,0));//rows+cols+2diag for player1 &2
    }

    int move(int row, int col, int player) {
        board[row][col]=player;
        int cnt=0;

        cnt=++counter[player-1][row];//for row
        if(cnt==n) return player;

        cnt=++counter[player-1][n+col];//for col
        if(cnt==n) return player;

        //for 2 diag
        if(row==col) cnt=++counter[player-1][2*n];
        if(cnt==n) return player;

        if(row+col==n-1) cnt=++counter[player-1][2*n+1];
        if(cnt==n) return player;

        return 0;
    }
};

void printResult(int testNumber, int actual, int expected) {
    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    cout << "Test " << testNumber << ": ";
    if (actual == expected) {
        cout << green << "PASS" << reset;
    } else {
        cout << red << "FAIL" << reset << " (Expected: " << expected << ", Got: " << actual << ")";
    }
    cout << endl;
}

int mainTest() {
    TicTacToe ticTacToe(3); // Initialize a 3x3 TicTacToe game

    vector<vector<int>> moves = {
            {0, 0, 1}, // Player 1 moves at (0, 0)
            {0, 2, 2}, // Player 2 moves at (0, 2)
            {2, 2, 1}, // Player 1 moves at (2, 2)
            {1, 1, 2}, // Player 2 moves at (1, 1)
            {2, 0, 1}, // Player 1 moves at (2, 0)
            {1, 0, 2}, // Player 2 moves at (1, 0)
            {2, 1, 1}  // Player 1 moves at (2, 1)
    };

    vector<int> expectedResults = {
            0, 0, 0, 0, 0, 0, 1 // Expected results for each move
    };

    for (int i = 0; i < moves.size(); ++i) {
        int row = moves[i][0];
        int col = moves[i][1];
        int player = moves[i][2];

        int result = ticTacToe.move(row, col, player);
        printResult(i + 1, result, expectedResults[i]);
    }

    return 0;
}