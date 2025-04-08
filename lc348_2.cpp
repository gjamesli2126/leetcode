#include <bits/stdc++.h>
#define testMain main
using namespace std;

class TicTacToe {
private:
    vector<int> cols;
    vector<int> rows;
    int diag;
    int antidiag;
    int n;
public:
    TicTacToe(int n):n(n) {
        cols.resize(n,0);
        rows.resize(n,0);
        diag=0;
        antidiag=0;
    }
    //player 1 is +1, player2 is -1
    int move(int row, int col, int player0) {
        int player=1;
        if(player0==2) player=-1;
        rows[row]+=player;
        cols[col]+=player;
        //is diag
        if(row==col) diag+=player;
        //is anti-diag
        if(row+col==n-1) antidiag+=player;

        //anyone win?
        if(abs(rows[row])==n || abs(cols[col])==n || abs(diag)==n || abs(antidiag)==n) return player0;

        return 0;


    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, int n, vector<vector<int>> moves, vector<int> expected) {
    // Create a TicTacToe object with board size n.
    TicTacToe* obj = new TicTacToe(n);
    vector<int> result;

    // For each move (row, col, player), call move() and record the result.
    for (const auto &move : moves) {
        int res = obj->move(move[0], move[1], move[2]);
        result.push_back(res);
    }

    // Compare result with expected output.
    bool pass = (result == expected);
    if(pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i] << (i < expected.size()-1 ? ", " : "");
        }
        cout << "], Got: [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "]" << endl;
    }
    delete obj;
}

int testMain(){
    // Example 1:
    // Input:
    // TicTacToe ticTacToe = new TicTacToe(3);
    // ticTacToe.move(0, 0, 1); // return 0 (no winner)
    // ticTacToe.move(0, 2, 2); // return 0 (no winner)
    // ticTacToe.move(2, 2, 1); // return 0 (no winner)
    // ticTacToe.move(1, 1, 2); // return 0 (no winner)
    // ticTacToe.move(2, 0, 1); // return 0 (no winner)
    // ticTacToe.move(1, 0, 2); // return 0 (no winner)
    // ticTacToe.move(2, 1, 1); // return 1 (player 1 wins)
    int n = 3;
    vector<vector<int>> moves = {
            {0, 0, 1},
            {0, 2, 2},
            {2, 2, 1},
            {1, 1, 2},
            {2, 0, 1},
            {1, 0, 2},
            {2, 1, 1}
    };
    vector<int> expected = {0, 0, 0, 0, 0, 0, 1};
    runTest(1, n, moves, expected);

    return 0;
}