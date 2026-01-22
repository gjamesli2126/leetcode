#include <bits/stdc++.h>
#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION
// ==========================================
class Solution {
public:
    /*
     * Find the length of the shortest transformation sequence.
     * Return 0 if no such sequence exists.
     */
    //using 雙向 BFS
    int ladderLength(const string& beginWord,const string& endWord, vector<string>& wordList) {
        int steps=0;
        unordered_set<string> dic(wordList.begin(),wordList.end());
        if(!dic.contains(endWord)) return 0;
        unordered_set<string> begin_set,end_set;
        begin_set.insert(beginWord);
        end_set.insert(endWord);
        steps++;
        while(!begin_set.empty() && !end_set.empty()){
            //永遠從小的一端開始 ---優化
            if(begin_set.size()>end_set.size()) swap(begin_set,end_set);
            //begin_Set is shorter
            unordered_set<string> next_level;
            for(string beginword:begin_set){
                for(char& c:beginword){
                    char org_c=c;
                    for(char newc='a';newc<='z';newc++){
                        if(newc==org_c) continue;
                        c=newc;
                        if(end_set.contains(beginword)) return steps+1;
                        if(dic.contains(beginword)){
                            next_level.insert(beginword);
                            dic.erase(beginword);
                        }
                    }
                    c=org_c;
                }
            }
            begin_set=next_level;
            ++steps;
        }

        return 0;
    }
};

// ==========================================
//  STRESS TEST INFRASTRUCTURE
// ==========================================

// Ground Truth Implementation (Standard BFS)
int referenceLadderLength(string beginWord, string endWord, vector<string> wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    // To avoid cycles, we remove words from dict as soon as we visit them
    // (Alternative to a separate visited set)
    if (dict.find(beginWord) != dict.end()) dict.erase(beginWord);

    while (!q.empty()) {
        auto [curr, steps] = q.front();
        q.pop();

        if (curr == endWord) return steps;

        // Try changing each character
        string original = curr;
        for (int i = 0; i < curr.size(); ++i) {
            char originalChar = curr[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == originalChar) continue;
                curr[i] = c;
                if (dict.count(curr)) {
                    if (curr == endWord) return steps + 1;
                    q.push({curr, steps + 1});
                    dict.erase(curr); // Mark as visited
                }
            }
            curr[i] = originalChar; // Restore for next position check
        }
    }
    return 0;
}

// Generate random word of length L
string randomWord(int len) {
    string s = "";
    for(int i=0; i<len; ++i) s += ('a' + rand()%26);
    return s;
}

// Generate a random solvable chain + noise
void generateRandomCase(int len, int chainLen, int noiseSize,
                        string& start, string& end, vector<string>& list) {
    start = randomWord(len);
    string curr = start;
    unordered_set<string> uniqueWords;
    uniqueWords.insert(start);

    // Create a guaranteed path
    vector<string> path;
    for(int i=0; i<chainLen; ++i) {
        // Change one random char
        int idx = rand() % len;
        char oldC = curr[idx];
        char newC = 'a' + rand() % 26;
        while(newC == oldC) newC = 'a' + rand() % 26;

        curr[idx] = newC;
        if(uniqueWords.find(curr) == uniqueWords.end()) {
            uniqueWords.insert(curr);
            path.push_back(curr);
        }
    }

    if(path.empty()) { end = randomWord(len); return; } // Should not happen often
    end = path.back();

    // Add path to list
    for(const string& w : path) list.push_back(w);

    // Add noise
    for(int i=0; i<noiseSize; ++i) {
        string noise = randomWord(len);
        if(uniqueWords.find(noise) == uniqueWords.end()) {
            uniqueWords.insert(noise);
            list.push_back(noise);
        }
    }

    // Shuffle list to hide the path
//    random_shuffle(list.begin(), list.end());
}

void printProgressBar(int current, int total) {
    int barWidth = 40;
    float progress = (float)current / total;
    cout << "\rProgress: [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %";
    cout.flush();
}

void runTest(int testNum, string testName, string begin, string end, vector<string> list, int expected, int& failedTests) {
    Solution sol;
    int actual = sol.ladderLength(begin, end, list);

    cout << "Test #" << testNum << " (" << testName << "): ";
    if (actual == expected) {
        cout << "\033[32mPassed\033[0m" << endl;
    } else {
        cout << "\033[31mFailed\033[0m (Exp: " << expected << ", Got: " << actual << ")" << endl;
        failedTests++;
    }
}

int mainTest() {
    srand(time(0));
    int failedTests = 0, totalTests = 0;

    cout << "=== STANDARD CASES ===" << endl;

    // Test 1: Example 1 from Image
    // hit -> hot -> dot -> dog -> cog (Len 5)
    vector<string> l1 = {"hot","dot","dog","lot","log","cog"};
    runTest(++totalTests, "Image Ex 1", "hit", "cog", l1, 5, failedTests);

    // Test 2: Example 2 from Image (No Path)
    // cog not in list
    vector<string> l2 = {"hot","dot","dog","lot","log"};
    runTest(++totalTests, "Image Ex 2 (Unreachable)", "hit", "cog", l2, 0, failedTests);

    // Test 3: Direct connection
    // hit -> hot (Len 2)
    vector<string> l3 = {"hot"};
    runTest(++totalTests, "Direct Connection", "hit", "hot", l3, 2, failedTests);

    // Test 4: Same word (Edge case, usually 0 or 1 depending on spec, LeetCode says 0 if endWord not in list?
    // Actually standard rule: sequence length. If begin==end, length 1.
    // But usually constraint says begin != end. Let's assume valid inputs.)

    cout << endl << "=== STRESS TESTS ===" << endl;
    int stressCount = 200;
    int stressFailures = 0;

    for(int i=0; i<stressCount; ++i) {
        string start, end;
        vector<string> list;
        // Generate small random graph
        generateRandomCase(3 + rand()%2, 2 + rand()%10, 10 + rand()%20, start, end, list);

        int expected = referenceLadderLength(start, end, list);

        Solution sol;
        int actual = sol.ladderLength(start, end, list);

        if (actual != expected) {
            stressFailures++;
            failedTests++;
            // cout << "Fail: " << start << " -> " << end << " Exp:" << expected << " Got:" << actual << endl;
        }
        if (i % 10 == 0) printProgressBar(i, stressCount);
    }
    printProgressBar(stressCount, stressCount);
    cout << endl;

    // Results
    double successRate = 1.0 - ((double)failedTests / totalTests);
    cout << endl << "==========================================" << endl;
    if (failedTests == 0) cout << "\033[32mAll Tests Passed (100%)\033[0m" << endl;
    else cout << "\033[31mSuccess Rate: " << (successRate * 100.0) << "%\033[0m" << endl;
    cout << "==========================================" << endl;

    return 0;
}