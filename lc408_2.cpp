#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    bool validWordAbbreviation(const string& word, const string& abbr) {
        //2 ptr
        int i=0;
        int j=0;
        while(i<word.length() && j<abbr.length()){
            if(isalpha(abbr[j])){
                if(abbr[j++]==word[i++]) continue;
                return false;
            }
            int j0=j;
            if(abbr[j0]=='0') return false;//no leading zero
            while(j<abbr.length() && isdigit(abbr[j])) {
                j++;
            }
            int num= stoi(abbr.substr(j0,j-j0));
            while(num--) i++;
            if(i>word.length()) return false;
        }
        return i == word.length() && j == abbr.length();//!!!
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
    runTest("3","internationalization","i5a11o1",true);
    return 0;
}