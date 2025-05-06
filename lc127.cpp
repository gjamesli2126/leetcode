#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int ladderLength(const string& beginWord,const string& endWord,const vector<string>& wordList) {
//        bitset<5001> shooted;//5001th is the begin word
        //pre process
        unordered_map<string,unordered_set<string>> graph;
        int L=beginWord.length();
        bool quickReturn=true;
        for(const string& word:wordList){
            if(word==endWord) quickReturn=false;
            for(int i=0;i<L;i++){
                string key=word.substr(0,i)+'*'+word.substr(i+1,L);//will return to the end of the string
                graph[key].insert(word);
            }
        }
        if(quickReturn) return 0;
        //BFS w/ queue
        queue<pair<string,int>> q;
        q.emplace(beginWord,1);
        unordered_set<string> shooted_from;//already visited
        while(!q.empty()){
            auto [word,level]=q.front();
            q.pop();
            shooted_from.insert(word);
            for(int i=0;i<L;i++){
                string key=word.substr(0,i)+'*'+word.substr(i+1,L);//will return to the end of the string
                for(const string& val:graph[key]){
                    if(val==endWord) return level+1;
                    if(!shooted_from.contains(val)) q.emplace(val,level+1);
                }
            }
        }

        return 0;
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