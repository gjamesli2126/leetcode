#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int arraySign(vector<int>& nums) {
        unsigned int negTimes=0;
        for(const int& i:nums){
            if(i<0) ++negTimes;
            if(i==0) return 0;
        }
        if(negTimes%2==0) return 1;
        return -1;
    }
};
int mainTest(){
    vector<vector<int>> testCases = {
            {-1, -2, -3, -4, 3, 2, 1},
            {1, 5, 0, 2, -3},
            {-1, 1, -1, 1, -1}
    };
    vector<int> expectedResults = {1, 0, -1};

    Solution solution;
    bool allPass = true;

    for(int i = 0; i < testCases.size(); i++){
        int result = solution.arraySign(testCases[i]);
        if(result == expectedResults[i]){
            cout << "\x1B[32mpass\033[0m Expected: " << expectedResults[i] << ", Got: " << result << endl;
        }else{
            cout << "\x1B[31mfail\033[0m Expected: " << expectedResults[i] << ", Got: " << result << endl;
            allPass = false;
        }
    }

    if(allPass){
        cout << "\x1B[34mAll Tests Passed (" << testCases.size() << "/" << testCases.size() << ")\033[0m" << endl;
    }else{
        cout << "\x1B[33mSome Tests Failed\033[0m" << endl;
    }

    return 0;
}
