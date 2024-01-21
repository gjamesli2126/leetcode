#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<vector<char>> *brd;
    const vector<pair<int,int>> dirs{
            {0,1},{1,0},{0,-1},{-1,0}
    };
    int rmax,cmax;
    unordered_set<char*> body;
    bool dfsBackTracking(const string_view& word,int i,pair<int,int> coord){
        if(i==word.size()-1) return true;
        auto& [r0,c0]=coord;
        body.insert(&((*brd)[r0][c0]));
        for(const auto& [dr,dc]:dirs){
            int r=r0+dr;
            int c=c0+dc;
            if(r<0 || c<0 || r==rmax || c==cmax || (*brd)[r][c]!=word[i+1] || body.contains(&(*brd)[r][c])) continue;
            if(dfsBackTracking(word,i+1,{r,c})) return true;
        }
        body.erase(&((*brd)[r0][c0]));
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        brd=&board;
        rmax=static_cast<int>(board.size());
        cmax=static_cast<int>(board[0].size());
        for(int r=0;r<rmax;++r){
            for(int c=0;c<cmax;++c){
                char ch=board[r][c];
                if(ch!=word[0]) continue;
//                body.clear();//no need as we did body.erase()
                if(dfsBackTracking(word,0, {r,c})) return true;
            }
        }
        return false;
    }
};

int mainTest() {
    vector<pair<vector<vector<char>>, string>> testCases = {
            {{{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}}, "ABCCED"},
            {{{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}}, "SEE"},
            {{{'A','B','C','E'}, {'S','F','C','S'}, {'A','D','E','E'}}, "ABCB"}
    };

    vector<bool> expectedResults = {
            true,
            true,
            false
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        auto& [board, word] = testCases[i];
        Solution solution; // Create a new Solution object for each test case
        bool result = solution.exist(board, word);

        cout << "Test Case " << i + 1 << " - ";
        cout << "Input: board = [";
        for (const auto& row : board) {
            cout << "[";
            for (size_t j = 0; j < row.size(); ++j) {
                cout << row[j];
                if (j < row.size() - 1) cout << ", ";
            }
            cout << "]";
        }
        cout << "], word = \"" << word << "\"\n";

        cout << "Output: " << boolalpha << result << "\n";
        cout << "Expected: " << boolalpha << expectedResults[i] << "\n";

        // Determine pass/fail status
        cout << "Test Result: ";
        if (result == expectedResults[i]) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
