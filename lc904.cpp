#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int maxWin=0;
        int fp,bp,len=int(fruits.size());
        unordered_map<int,int> mp;
        for(fp=0,bp=0;bp<len;++bp){
            ++mp[fruits[bp]];
            while(mp.size()>2){
                --mp[fruits[fp]];
                if(mp[fruits[fp]]==0) mp.erase(fruits[fp]);
                ++fp;
            }
            maxWin=max(maxWin,bp-fp+1);
        }
        return maxWin;
    }
};

int mainTest() {
    Solution solution;

    // Test Cases
    vector<vector<int>> testCases = {
            {1,2,1},             // Example 1
            {0,1,2,2},           // Example 2
            {1,2,3,2,2},         // Example 3
            {1,2,3,2,2,4,4,4}    // New Test Case
    };

    // Expected Outputs
    vector<int> expectedOutputs = {3, 3, 4, 5}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        int actual = solution.totalFruit(testCases[i]);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
