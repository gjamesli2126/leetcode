#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool validWordAbbreviation(const string& word,const string& abbr) {
        int i=0,j=0;
        int num=0;
        while(j<abbr.length()){
            if(isdigit(abbr[j])){
                if(abbr[j]=='0') return false;
                num=0;
                while(isdigit(abbr[j]) && j<abbr.length()){
                    num = 10 * num + abbr[j] - '0';
                    j++;
                }
                i+=num;
            }else{
                if(i>=word.length() || word[i]!=abbr[j]) return false;
                i++;
                j++;
            }
        }
        return i==word.length();
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