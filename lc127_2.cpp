#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& beginWord, const string& endWord, vector<string> wordList, int expected) {
    Solution sol;
    int result = sol.ladderLength(beginWord, endWord, wordList);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: ladderLength(\"" << beginWord << "\", \"" << endWord
             << "\", wordList) = " << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: ladderLength(\"" << beginWord << "\", \"" << endWord
             << "\", wordList) = " << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: beginWord = "hit", endWord = "cog",
    //        wordList = ["hot","dot","dog","lot","log","cog"]
    // Expected Output: 5
    runTest(1, "hit", "cog", {"hot","dot","dog","lot","log","cog"}, 5);

    // Example 2:
    // Input: beginWord = "hit", endWord = "cog",
    //        wordList = ["hot","dot","dog","lot","log"]
    // Expected Output: 0
    runTest(2, "hit", "cog", {"hot","dot","dog","lot","log"}, 0);

    return 0;
}