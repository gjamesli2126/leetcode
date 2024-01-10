#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<char,int> cfmap;
public:
    int characterReplacement(const string& str, const int k) {
        if(k==1){

        }
        int l=0,r;
        int maxWin=0;
        int maxFreq=0;
        int slen=int(str.length());
        for(r=0;r<slen;++r){
            char c=str[r];
            cfmap[c]++;
            maxFreq=max(maxFreq,cfmap[c]);
            while(r-l+1-maxFreq>k) cfmap[str[l++]]--;
            maxWin=max(maxWin,r-l+1);
        }
        return maxWin;
    }
};

int mainTest() {
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
    };



    struct TestCase {
        string s;
        int k;
        int expected;
    };

    vector<TestCase> testCases = {
            {"ABAB", 2, 4},       // Test case 1
            {"AABABBA", 1, 4},    // Test case 2
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        Solution solution;
        int result = solution.characterReplacement(testCases[i].s, testCases[i].k);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
