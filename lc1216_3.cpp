#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
private:
    int dfsNeedK(const string& s,int l,int r,vector<vector<int>>& memo){
        if(l>=r) return 0;
        int& ans=memo[l][r];
        if(ans!=-1) return ans;
        if(s[l]==s[r]) ans= dfsNeedK(s,l+1,r-1,memo);
        else ans=1+min(dfsNeedK(s,l+1,r,memo), dfsNeedK(s,l,r-1,memo));
        return ans;
    }
public:
    bool isValidPalindrome(const string& s, int k) {
        int sl=s.length();
        if(sl<=1) return true;
        vector<vector<int>> memo(sl,vector<int>(sl,-1));
        return dfsNeedK(s,0,sl-1,memo)<=k;

    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, int k, bool expected) {
    Solution sol;
    bool result = sol.isValidPalindrome(s, k);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isValidPalindrome(\"" << s << "\", " << k << ") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isValidPalindrome(\"" << s << "\", " << k << ") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "abcdeca", k = 2
    // Expected Output: true (by removing 'b' and 'e', "acdca" is a palindrome)
    runTest(1, "abcdeca", 2, true);

    // Test Case 2:
    // Input: s = "abbababa", k = 1
    // Expected Output: true
    runTest(2, "abbababa", 1, true);

    return 0;
}