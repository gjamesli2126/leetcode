#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int minAddToMakeValid(string s) {
        int quota=0,invalid=0;
        for(const char& c:s){
            if(!quota && c==')') ++invalid;
            else if(quota && c==')') --quota;
            else if(c=='(') ++quota;
        }
        return invalid+quota;
    }
};

int mainTest() {
    vector<pair<string, int>> testCases = {
            {"())", 1},
            {"(((", 3},
            // Add more test cases as needed
    };

    for (auto& [testCase, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input: \"" << testCase << "\"\n";
        int result = solution.minAddToMakeValid(testCase);
        cout << "Output: " << result << "\n";

        // Determine pass/fail status
        if (result == expected) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
