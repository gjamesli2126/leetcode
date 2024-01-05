#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<pair<int,int>> stk;
        int len=int(heights.size());
        int maxArea=0;
        for(int i=0;i<len;++i){
            int startI=i;
            while(!stk.empty() && stk.top().second>heights[i]){
                auto& [ind,high]=stk.top();
                int width=i-ind;
                maxArea= max(maxArea,width*high);
                startI=ind;
                stk.pop();
            }
            stk.push({startI,heights[i]});
        }
        while(!stk.empty()){
            auto& [ind,high]=stk.top();
            int width=len-ind;
            maxArea=max(maxArea,high*width);
            stk.pop();
        }
        return maxArea;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        }
    };

    Solution solution;

    // Test case 1
    vector<int> heights1 = {2,1,5,6,2,3};
    test(solution.largestRectangleArea(heights1), 10, "Test Case 1");

    // Test case 2
    vector<int> heights2 = {2,4};
    test(solution.largestRectangleArea(heights2), 4, "Test Case 2");

    // Add more test cases if necessary.
    // Test case 3
    vector<int> heights = {2,1,2};
    test(solution.largestRectangleArea(heights), 3, "Test Case 3");
    return 0;
}
