#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //by vertical scan
        string ans;
        for(int c=0;c<strs[0].length();c++){//take reference of the first string
            char first_charc=strs[0][c];
            for(int r=1;r<strs.size();r++){
                if(first_charc!=strs[r][c]) return ans;
            }
            //assume are the same charc
            ans+=first_charc;
        }
        return ans;
    }
};

void runTest(int testNum, const vector<string>& strs, const string& expected) {
    Solution sol;
    string result = sol.longestCommonPrefix(const_cast<vector<string>&>(strs));
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: got [" << result << "] expected [" << expected << "]\033[0m\n";
    }
}

int mainTest() {
    // Example tests
    runTest(1, {"flower", "flow", "flight"}, "fl");
    runTest(2, {"dog", "racecar", "car"}, "");
    // Additional tests
    runTest(3, {"interspecies", "interstellar", "interstate"}, "inters");
    runTest(4, {"throne", "throne"}, "throne");
    runTest(5, {"", "b", "c"}, "");
    return 0;
}