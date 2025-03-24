#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    bool chkpal(const string &v,int l,int r){
        while(l<r){
            if(v[l]!=v[r]) return false;
            l++;
            r--;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        int credit=1;
        int l=0;
        int r=s.length()-1;
        while(l<r){
            if(s[l]==s[r]){
                l++;
                r--;
            }
            else{
                return chkpal(s,l+1,r) || chkpal(s,l,r-1);
            }
        }
        return true;
    }
};

// Helper function to convert bool to "true"/"false" string.
string boolToString(bool b) {
    return b ? "true" : "false";
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, string s, bool expected) {
    Solution sol;
    bool result = sol.validPalindrome(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: Input: "
             << s << " => Output: " << boolToString(result) << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Input: "
             << s << " => Expected: " << boolToString(expected)
             << ", Got: " << boolToString(result) << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: s = "aba"
    // Expected Output: true
    runTest(1, "aba", true);

    // Example 2:
    // Input: s = "abca"
    // Expected Output: true (by deleting 'c')
    runTest(2, "abca", true);

    // Example 3:
    // Input: s = "abc"
    // Expected Output: false
    runTest(3, "abc", false);

    return 0;
}