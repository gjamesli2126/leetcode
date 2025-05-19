#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int countSubstrings(const string& s) {
        if(s.length()<=1) return 1;
        int acc=0;
        //go over with odd sum
        for(int i=0;i<s.length();i++){
            int l=i;
            int r=i;
            while(l>=0 && r<s.length() && s[l--]==s[r++]) ++acc;
        }
        //go over with even sum
        for(int i=1;i<s.length();i++){
            int l=i-1;
            int r=i;
            while(l>=0 && r<s.length() && s[l--]==s[r++]) ++acc;

        }
        return acc;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, int expected) {
    Solution sol;
    int result = sol.countSubstrings(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: countSubstrings(\"" << s << "\") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: countSubstrings(\"" << s << "\") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "abc"
    // Expected Output: 3 (palindromic substrings: "a", "b", "c")
    runTest(1, "abc", 3);

    // Test Case 2:
    // Input: s = "aaa"
    // Expected Output: 6 (palindromic substrings: "a", "a", "a", "aa", "aa", "aaa")
    runTest(2, "aaa", 6);

    return 0;
}