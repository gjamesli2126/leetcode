#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    bool validPalindrome(const string& s) {
        //2-pass: 以右為準 or 以左為準 有過就好
        int sl=s.length();
        int l,r;
        int chances=2;
        bool canDel=true;
        l=0;
        r=sl-1;
        while(l<r){
            if(s[l]!=s[r]){
                if(!canDel){
                    chances--;
                    break;
                }
                canDel= false;
                l++;
            }else{
                l++;
                r--;
            }
        }
        if(chances==2) return true;
        canDel=true;
        l=0;
        r=sl-1;
        while(l<r){
            if(s[l]!=s[r]){
                if(!canDel) return false;
                canDel=false;
                r--;
            }else{
                l++;
                r--;
            }
        }
        return chances;
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