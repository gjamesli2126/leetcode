#include <bits/stdc++.h>
#define testMain main
using namespace std;

class TicTacToe {
private:
    struct Stat{
        vector<int> rCnt;
        vector<int> cCnt;
        int diagCnt;
        int adiagCnt;
    };
    //player1 stat & player2 stat
    vector<Stat> player_stat;//cannot use platyer_stat(n) as this does not support at declarion here;
    int n;
    inline bool onDiag(int r,int c){
        return r==c;
    }
    inline bool onADiag(int r,int c){
        return r+c==n-1;
    }
    int insertFn(int r,int c,int p){

        if(onDiag(r,c)) player_stat[p].diagCnt++;
        if(player_stat[p].diagCnt==n) return p;
        if(onADiag(r,c)) player_stat[p].adiagCnt++;
        if(player_stat[p].adiagCnt==n) return p;
        player_stat[p].rCnt[c]++;
        if(player_stat[p].rCnt[c]==n) return p;
        player_stat[p].cCnt[r]++;
        if(player_stat[p].cCnt[r]==n) return p;
        return 0;

    }
public:
    TicTacToe(int n):player_stat(3),n(n){
        //count: r_tbl,c_tbl,diag_tbl,adiag_tbl==3 -> win
        //不用建立他媽的 tbl的table
        for(int i=1;i<3;i++){
            player_stat[i].rCnt.resize(n);
            player_stat[i].cCnt.resize(n);
        }
    }

    int move(int row, int col, int player) {
        return insertFn(row,col,player);

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