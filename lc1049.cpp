#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    int target;
    int stoneSum;
    int maxInd;
    unordered_map<string,int> dp;
    vector<int> *stones;
    int difDfs(int total,int i){
        if(total>=target || i==maxInd) return abs(total-(stoneSum-total));
        // pair(i,total) to str
        string pr= to_string(i)+","+ to_string(total);
        if(dp.find(pr)!=dp.end()) return dp[pr];
        dp[pr]=min(difDfs(total+(*stones)[i],i+1), difDfs(total,i+1));
        return dp[pr];
    }
public:
    int lastStoneWeightII(vector<int>& stones0) {
        stones=&stones0;
        stoneSum= accumulate(stones0.begin(),stones0.end(),0);
        target=stoneSum/2;
        maxInd=int(stones0.size())-1;
        return difDfs(0,0);
    }
};

int mainTest() {
    // Creating a new instance of Solution for each test case
    vector<vector<int>> testCases = {
            {2,7,4,1,8,1},   // Example 1
            {31,26,33,21,40}, // Example 2
            {89,23,100,93,82,98,91,85,33,95,72,98,63,46,17,91,92,72,77,79,99,96,55,72,24,98,79,93,88,92}
    };

    vector<int> expectedOutputs = {1, 5,0}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
        Solution solution; // Create a new Solution object for each test case
        int actual = solution.lastStoneWeightII(testCases[i]);
        bool status = (actual == expectedOutputs[i]);
        cout << "Test " << i + 1 << ": "
             << "Input: stones = [";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            cout << testCases[i][j];
            if (j < testCases[i].size() - 1) cout << ", ";
        }
        cout << "], Expected: " << expectedOutputs[i]
             << ", Actual: " << actual
             << ", Status: " << (status ? "PASS" : "FAIL") << endl;
    }
    return 0;
}
