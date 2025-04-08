#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if(s.length()>t.length()) return false;
        int p1=0;
        int p2=0;
//        bool ismatch=false;
        while(p1<s.length() && p2<t.length()){
//            ismatch=false;
//            while(p2<t.length() && s[p1]!=t[p2]) p2++;
//            if(s[p1]==t[p2]) ismatch=true;
            if(s[p1]==t[p2]) p1++;
            p2++;
        }
        return p1==s.length();// && ismatch;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, string t, bool expected) {
    Solution sol;
    bool result = sol.isSubsequence(s, t);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isSubsequence(\"" << s << "\", \"" << t << "\") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isSubsequence(\"" << s << "\", \"" << t << "\") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "abc", t = "ahbgdc"
    // Expected Output: true
    runTest(1, "abc", "ahbgdc", true);

    // Test Case 2:
    // Input: s = "axc", t = "ahbgdc"
    // Expected Output: false
    runTest(2, "axc", "ahbgdc", false);
    runTest(4, "", "ahbgdc", true);
    runTest(3, "b", "c", false);

    return 0;
}