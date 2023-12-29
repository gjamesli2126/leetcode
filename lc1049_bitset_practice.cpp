#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {

public:
    int lastStoneWeightII(vector<int>& stones) {
        int totalSum= accumulate(stones.begin(),stones.end(),0);
        int half= totalSum/2;
        bitset<30*100/2+1> possibleSum;
        possibleSum.set(0);//must have sum=0
//        大家一起向左推
        for(const int& weight:stones) possibleSum|=possibleSum<<weight;
//        從較小的那一半開始看合理 sum
        for(int smallerSum=half;smallerSum>=0;--smallerSum){
            if(possibleSum.test(smallerSum)) return (totalSum-smallerSum)-smallerSum;
        }// 注意: 當 smallerSum是0 則 另一半就是 totalSum
        return 0;
    }
};


int mainTest() {
    Solution solution;
    vector<vector<int>> testCases = {
            {2,7,4,1,8,1},   // Example 1
            {31,26,33,21,40}, // Example 2
            {91}
    };

    vector<int> expectedOutputs = {1, 5,91}; // Corresponding expected outputs for the test cases

    for (int i = 0; i < testCases.size(); ++i) {
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
