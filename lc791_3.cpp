#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    string customSortString(const string& order,const string& s) {
        if(s.length()==1) return s;
        unordered_map<char,int> char_freq;
        for(char c:s) char_freq[c]++;
        string ans;
        for(char c:order){
            ans+=string(char_freq[c],c);
            char_freq[c]=0;
        }
        //remaining
        for(auto& [c,f]:char_freq){
            if(f) ans+=string(f,c);
        }
        return ans;
    }
};
// Helper function to check if 'result' is a valid permutation of s
// that respects the relative order of characters in 'order'.
bool isValidCustomSortString(const string &order, const string &s, const string &result) {
    // 1. Check that result is a permutation of s.
    if (result.size() != s.size()) return false;
    vector<int> freqS(26, 0), freqResult(26, 0);
    for (char c : s) {
        freqS[c - 'a']++;
    }
    for (char c : result) {
        freqResult[c - 'a']++;
    }
    if (freqS != freqResult) return false;

    // 2. For characters that appear in 'order', ensure that their relative order
    // in 'result' is the same as in 'order'.
    unordered_map<char, int> orderPos;
    for (int i = 0; i < order.size(); i++) {
        orderPos[order[i]] = i;
    }
    // Build a filtered string of only those characters that are in 'order'
    string filtered;
    for (char c : result) {
        if (orderPos.count(c)) {
            filtered.push_back(c);
        }
    }
    // Check that 'filtered' is sorted according to the order defined in 'order'
    for (int i = 0; i < filtered.size() - 1; i++) {
        if (orderPos[filtered[i]] > orderPos[filtered[i + 1]])
            return false;
    }
    return true;
}

void runTest(int testNum, string order, string s) {
    Solution sol;
    string result = sol.customSortString(order, s);
    if (isValidCustomSortString(order, s, result)) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: customSortString(\"" << order << "\", \"" << s
             << "\") = \"" << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: customSortString(\"" << order << "\", \"" << s
             << "\") = \"" << result << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: order = "cba", s = "abcd"
    // Valid output must ensure that 'c', 'b', and 'a' appear in that order.
    runTest(1, "cba", "abcd");

    // Test Case 2:
    // Input: order = "bcafg", s = "abcd"
    // Valid output must ensure that 'b', 'c', and 'a' appear in that order.
    runTest(2, "bcafg", "abcd");

    return 0;
}