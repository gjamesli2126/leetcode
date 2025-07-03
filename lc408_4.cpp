#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    bool validWordAbbreviation(const string& word,const string& abbr) {
        //first chk abbr, Then chl word
        int iw=0;
        int ia=0;
        int lw=word.length();
        int la=abbr.length();
        while (ia<la){
            //if abbr is digit
            if(isdigit(abbr[ia])){
                //this line means when we first saw a digiy
                if(abbr[ia]=='0') return false;
                int num=0;
                while(ia<la && isdigit(abbr[ia])) num=10*num+abbr[ia++]-'0';
                iw+=num;
            }else{//if is char
                if(iw>=lw || word[iw]!=abbr[ia]) return false;
                iw++;
                ia++;
            }

        }
        return iw==lw;
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