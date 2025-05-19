#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    int dfsNeedK(const string& s,vector<vector<int>>& memo, int i,int j){
        if(i>=j) return 0;
        int &ans=memo[i][j];
        if(ans!=-1) return ans;
        if(s[i]==s[j]) ans= dfsNeedK(s,memo,i+1,j-1);//no need to add 1
        else ans= 1+min(dfsNeedK(s,memo,i+1,j), dfsNeedK(s,memo,i,j-1));
        return ans;
    }

public:
    bool isValidPalindrome(const string& s, int k) {
        int n=s.length();
        if(n<=1) return true;
        vector<vector<int>> memo(n,vector<int>(n,-1));
        return dfsNeedK(s,memo,0,n-1)<=k;
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