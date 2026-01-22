#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string reorganizeString(const string& org){
        if(org.empty()) return "";
        unordered_map<int,int> count;
        //gather the freq
        for(char c:org) count[c]++;
        //create the minHeap from count map
        priority_queue<pair<int,char>> maxHeap;
        string res;
        //check if the max freq's charc is no more than half of the string len
        for(const auto& [c,freq]:count) maxHeap.emplace(freq,c);//sort by freq
        if(maxHeap.top().first>(1+org.length())/2) return "";
        pair<int,char> block={0,'#'};
        while(!maxHeap.empty()){
            auto current=maxHeap.top();
            auto& [freq,c]=current;
            maxHeap.pop();
            res+=c;
            freq--;
            if(block.first) maxHeap.emplace(block);
            block=current;
        }

        return res;
    }
};

// ==========================================
// Test Harness
// ==========================================

#define mainTest main

void runTest(string s, string testName) {
    Solution sol;
    string result = sol.reorganizeString(s);

    cout << "Test: " << testName << " | Input: \"" << s << "\"" << endl;

    // Check if result is explicitly empty (Impossible case)
    if (result == "") {
        // Verify if it SHOULD be impossible
        unordered_map<char, int> m;
        int maxF = 0;
        for(char c : s) m[c]++;
        for(auto p : m) maxF = max(maxF, p.second);

        if (maxF > (s.length() + 1) / 2) {
            cout << "  -> Output: \"\" (Correct - Impossible)" << endl;
        } else {
            cout << "  -> Output: \"\" (FAILURE - Should be possible)" << endl;
        }
    }
    else {
        // 1. Verify Adjacency
        bool adjacentConflict = false;
        for (size_t i = 1; i < result.length(); ++i) {
            if (result[i] == result[i-1]) {
                adjacentConflict = true;
                break;
            }
        }

        // 2. Verify Character Counts (Permutation correctness)
        unordered_map<char, int> originalCounts;
        unordered_map<char, int> resultCounts;
        for(char c : s) originalCounts[c]++;
        for(char c : result) resultCounts[c]++;

        if (!adjacentConflict && originalCounts == resultCounts) {
            cout << "  -> Output: \"" << result << "\" (PASS)" << endl;
        } else {
            cout << "  -> Output: \"" << result << "\" (FAIL - Logic Error)" << endl;
            if (adjacentConflict) cout << "     Reason: Adjacent duplicates found." << endl;
            if (originalCounts != resultCounts) cout << "     Reason: Character counts do not match." << endl;
        }
    }
    cout << "------------------------------------------------" << endl;
}

int mainTest() {
    // Example 1: Valid case
    runTest("aab", "Example 1");

    // Example 2: Impossible case (a is 3, length 4 -> 3 > (4+1)/2)
    runTest("aaab", "Example 2");

    // Test 3: Complex Valid
    // "vvvlo" -> v:3, len:5. 3 <= (5+1)/2. Valid. Possible: "vlvov"
    runTest("vvvlo", "Complex Valid");

    // Test 4: Empty string
    runTest("", "Empty Input");

    // Test 5: Single char
    runTest("z", "Single Char");

    return 0;
}