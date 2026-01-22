#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <random>
#include <ctime>

// Macro for main function to avoid conflicts
#define mainTest main

using namespace std;

// ==========================================
// YOUR SOLUTION CLASS (Optimized BFS)
// ==========================================
class Solution {
public:
    int ladderLength(const string& beginWord,const string& endWord,const vector<string>& wordList) {
        //using 雙向 BFS, from st && from end 同時擴散
        unordered_set<string> word_bank;
        for(const string& s:wordList) word_bank.emplace(s);
        if(!word_bank.contains(endWord)) return 0;
        unordered_set<string> begin_set,end_set;
        begin_set.emplace(beginWord);
        end_set.emplace(endWord);
        int steps=1;
        while(!begin_set.empty() && !end_set.empty()){
           if(begin_set.size()>end_set.size()) swap(begin_set,end_set);//so always on the shorter side(begin_set
           unordered_set<string> nextLevel_set;
           for(string begin_word:begin_set){//unorered_set 裡面的 element 是 immutable 否則會破壞 hash
               //要看 begin set 與 end_set 交織
               //嘗試變換每個字母
               for(char& c:begin_word){
                   char org_c=c;
                   for(char newc='a';newc<='z';newc++){
                       if(newc==org_c) continue;
                       if(end_set.contains(begin_word)) return steps+1;//已撞到 end_set
                       c=newc;
                       if(word_bank.contains(begin_word)){
                           nextLevel_set.emplace(begin_word);
                           word_bank.erase(begin_word);
                       }
                   }
                   c=org_c;
               }
           }
           begin_set=nextLevel_set;
           ++steps;
        }
        return 0;
    }
};

// ==========================================
// TEST HARNESS UTILITIES
// ==========================================

// Trusted Reference Solver (Identical logic to verify random cases)
int referenceLadderLength(string beginWord, string endWord, vector<string> wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    if (dict.count(beginWord)) dict.erase(beginWord);

    while (!q.empty()) {
        auto [curr, steps] = q.front();
        q.pop();

        if (curr == endWord) return steps;

        for (int i = 0; i < curr.size(); ++i) {
            char originalChar = curr[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == originalChar) continue;
                curr[i] = c;
                if (dict.count(curr)) {
                    q.push({curr, steps + 1});
                    dict.erase(curr);
                }
            }
            curr[i] = originalChar;
        }
    }
    return 0;
}

// Helper: Run a single test
void runTest(int testId, string beginWord, string endWord, vector<string> wordList, int expected, int& failedTests) {
    Solution sol;
    int actual = sol.ladderLength(beginWord, endWord, wordList);

    cout << "Test #" << testId << ": ";
    if (actual == expected) {
        cout << "\033[32m" << "Passed" << "\033[0m";
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m";
        cout << " | Expected: " << expected << ", Actual: " << actual;
        cout << " | Start: " << beginWord << ", End: " << endWord;
        failedTests++;
    }
    cout << endl;
}

// Helper: Generate a guaranteed connected chain + random noise
struct StressCase {
    string begin;
    string end;
    vector<string> list;
    int expectedLength;
};

StressCase generateStressTest(int len, int chainLen) {
    string current(len, 'a');
    string begin = current;
    vector<string> list;

    // Create a simple chain: aaaaa -> baaaa -> bbaaa ...
    // Note: This logic assumes len >= chainLen roughly or we handle wrap around.
    // For simplicity, we just mutate indices sequentially.

    for (int i = 0; i < chainLen - 1; ++i) {
        // mutate index (i % len) to 'b'
        current[i % len] = 'b';
        list.push_back(current);
    }
    string end = current;

    // Add random noise
    for(int k=0; k<20; ++k) {
        string noise = begin;
        noise[rand() % len] = (char)('a' + (rand() % 26));
        list.push_back(noise);
    }

    // Shuffle list
    // (std::shuffle is better but rand swap is enough for simple harness)
    for(int i=0; i<list.size(); ++i) swap(list[i], list[rand()%list.size()]);

    // Calculate TRUE shortest path using reference (because noise might create shortcuts!)
    int trueDist = referenceLadderLength(begin, end, list);

    return {begin, end, list, trueDist};
}

int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Manual Corner Cases ===" << endl;

    // Test 1: LeetCode Example 1
    {
        vector<string> list = {"hot","dot","dog","lot","log","cog"};
        runTest(++totalTests, "hit", "cog", list, 5, failedTests);
    }

    // Test 2: LeetCode Example 2 (End missing)
    {
        vector<string> list = {"hot","dot","dog","lot","log"};
        runTest(++totalTests, "hit", "cog", list, 0, failedTests);
    }

    // Test 3: Direct 1-step connection
    {
        vector<string> list = {"b"};
        runTest(++totalTests, "a", "b", list, 2, failedTests);
    }


//    // Test 4: Disconnected graph (Bridge missing)
//    {
//        // a -> b (in list) -> c (missing) -> d (in list)
//        vector<string> list = {"b", "d"};
//        runTest(++totalTests, "a", "d", list, 0, failedTests);
//    }
//
//    // Test 5: Start word in list (Shouldn't affect length logic if handled right)
//    {
//        vector<string> list = {"a", "b", "c"};
//        // a -> b -> c : length 3. If 'a' is in list, we treat it same as start node.
//        runTest(++totalTests, "a", "c", list, 3, failedTests);
//    }

    cout << "\n=== Randomized Stress Tests (Wait...) ===" << endl;

    for (int i = 0; i < 50; i++) {
        // Generate chain of length 3 to 8, word len 5
        StressCase sc = generateStressTest(5, (rand() % 6) + 2);

        // Randomly remove endWord sometimes to test "Not Found" logic
        if (rand() % 4 == 0) { // 25% chance to break it
            // Remove endWord from list
            vector<string> brokenList;
            for(string s : sc.list) if(s != sc.end) brokenList.push_back(s);
            runTest(++totalTests, sc.begin, sc.end, brokenList, 0, failedTests);
        } else {
            runTest(++totalTests, sc.begin, sc.end, sc.list, sc.expectedLength, failedTests);
        }
    }

    // ==========================================
    // ERROR RATE REPORT
    // ==========================================
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m";
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m";
    }
    cout << endl;

    return 0;
}