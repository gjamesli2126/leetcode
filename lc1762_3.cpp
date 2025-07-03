#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        stack<int> istk;
        for(int i=0;i<heights.size();i++){
            while(!istk.empty() && heights[istk.top()]<=heights[i]) istk.pop();
            istk.push(i);
        }
        int istks=istk.size();
        vector<int> ans(istks);
        for(int i=0;i<istks;i++) ans[istks-i-1]=istk.top(),istk.pop();

        return ans;
    }
};
// Helper function to print a vector in [a,b,c,...] format.
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size())
            cout << ",";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, vector<int> heights, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.findBuildings(heights);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        printVector(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected ";
        printVector(expected);
        cout << " but got ";
        printVector(result);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: heights = [4,2,3,1]
    // Expected Output: [0,2,3]
    runTest(1, {4,2,3,1}, {0,2,3});

    // Test Case 2:
    // Input: heights = [4,3,2,1]
    // Expected Output: [0,1,2,3]
    runTest(2, {4,3,2,1}, {0,1,2,3});

    // Test Case 3:
    // Input: heights = [1,3,2,4]
    // Expected Output: [3]
    runTest(3, {1,3,2,4}, {3});

    // Test Case 4:
    // Input: heights = [2,2,2,2]
    // Expected Output: [3]
    runTest(4, {2,2,2,2}, {3});
    return 0;
}