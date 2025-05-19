#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(const string& s) {
        //sliding window
        int l=0;
        int r;
        int glob_max=0;
        unordered_set<char> inDaHouse;//max =256 charc all the ascii table
        for(r=0;r<s.length();r++){
            char c=s[r];
            if(!inDaHouse.contains(c)) inDaHouse.insert(c);
            else {
                while(c!=s[l]) inDaHouse.erase(s[l++]);
                l++;//just shift l, cuz erase the dup and add it back again.
            }
            glob_max= max(glob_max,r-l+1);
        }
        return glob_max;
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
    runTest(4, "", 0);
    return 0;
}