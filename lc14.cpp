#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==1) return strs[0];
        else if(strs.empty()) return "";
        string prefix;
        for(int i=0;;i++){
            char c=strs[0][i];
            for(int j=1;j<strs.size();j++){
                const string& str=strs[j];
                if(i==str.length() || c!=str[i]) return prefix;
            }
            prefix+=c;
        }
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<string> strs, string expected) {
    Solution sol;
    string result = sol.longestCommonPrefix(strs);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: longestCommonPrefix(...) = \""
             << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: longestCommonPrefix(...) = \""
             << result << "\", expected \"" << expected
             << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: strs = ["flower","flow","flight"]
    // Output: "fl"
    runTest(1, {"flower","flow","flight"}, "fl");

    // Example 2:
    // Input: strs = ["dog","racecar","car"]
    // Output: ""
    runTest(2, {"dog","racecar","car"}, "");

    // Additional Test Case:
    // Input: strs = ["interspecies","interstellar","interstate"]
    // Output: "inters"
    runTest(3, {"interspecies","interstellar","interstate"}, "inters");

    return 0;
}