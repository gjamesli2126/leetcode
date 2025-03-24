#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool isPalindrome(const string& s) {
        int l=0,r=s.length()-1;
        while(l<r){
            while(l<r && !isalnum(s[l])) l++;
            while(l<r && !isalnum(s[r])) r--;
            if(tolower(s[l])!= tolower(s[r])) return false;
            l++;
            r--;
        }
        return true;
    }
};

// Helper function to convert a boolean value to string.
string boolToString(bool b) {
    return b ? "true" : "false";
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, string s, bool expected) {
    Solution sol;
    bool result = sol.isPalindrome(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: Input: \"" << s
             << "\" => Output: " << boolToString(result)
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: Input: \"" << s
             << "\" => Expected: " << boolToString(expected)
             << ", Got: " << boolToString(result)
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "A man, a plan, a canal: Panama"
    // Expected Output: true
    runTest(1, "A man, a plan, a canal: Panama", true);

    // Test Case 2:
    // Input: s = "race a car"
    // Expected Output: false
    runTest(2, "race a car", false);

    // Test Case 3:
    // Input: s = " "
    // Expected Output: true
    runTest(3, " ", true);

    return 0;
}