#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(const string& s) {
        // TODO: Implement sliding window or other approach.
        if(s.empty()) return 0;
//        sliding window need to use 2 ptr, Jump using ascii table is better
        int l=0,r;
        int max_len=0;
        vector<int> ascii_last_index(256,-1);
        for(r=0;r<s.length();r++){
            if(l<=ascii_last_index[s[r]]) l=ascii_last_index[s[r]]+1;
            ascii_last_index[s[r]]=r;
            max_len=max(max_len,r-l+1);
        }
        return max_len;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& s, int expected) {
    Solution sol;
    int result = sol.lengthOfLongestSubstring(s);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: lengthOfLongestSubstring(\"" << s << "\") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: lengthOfLongestSubstring(\"" << s << "\") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: s = "abcabcbb"
    // Output: 3
    runTest(1, "abcabcbb", 3);

    // Example 2:
    // Input: s = "bbbbb"
    // Output: 1
    runTest(2, "bbbbb", 1);

    // Example 3:
    // Input: s = "pwwkew"
    // Output: 3
    runTest(3, "pwwkew", 3);

    return 0;
}