#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        if(word.empty() && abbr.empty()) return true;
        int i, j;
        int num = 0;
        for(i = 0, j = 0; j < abbr.length(); j++){
            char abb_c = abbr[j];
            // If the character is a digit, accumulate the number (with leading zero check)
            if(isdigit(abb_c)){
                if(num == 0 && abb_c == '0') return false; // invalid leading zero
                num = 10 * num + (abb_c - '0');
            } else {
                // If a number was accumulated, apply it before comparing letters.
                if(num){
                    i += num;
                    num = 0;
                }
                if(i >= word.length() || word[i] != abb_c) return false;
                i++;
            }
        }
        // If digits remain at the end, apply them.
        if(num) i += num;
        return i == word.length();
    }
};

// Helper function to run and check a test case.
// If the output doesn't match the expected result, the message is printed in red.
void runTest(const string& testName, const string& word, const string& abbr, bool expected) {
    Solution sol;
    bool result = sol.validWordAbbreviation(word, abbr);
    if (result == expected) {
        cout << testName << " Passed: " << (result ? "true" : "false") << endl;
    } else {
        // ANSI escape code for red text: "\033[1;31m", reset: "\033[0m"
        cout << "\033[1;31m" << testName << " Failed: Expected "
             << (expected ? "true" : "false") << " but got "
             << (result ? "true" : "false") << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    runTest("Test Case 1", "internationalization", "i12iz4n", true);

    // Test Case 2:
    runTest("Test Case 2", "apple", "a2e", false);

    // Additional test cases can be added here.

    return 0;
}