#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //sort according to hte leftS
        auto cmp=[&](vector<int>& v1, vector<int>& v2){
            return v1[0]<v2[0];
        };
        sort(intervals.begin(),intervals.end(), cmp);
        // the first pari's right vs (1. second's left 2, second's right)
        int vl=intervals.size();
        vector<vector<int>> ans;
        ans.push_back(intervals.front());
        for(int i=1;i<vl;i++){
            vector<int>& f=ans.back();
            vector<int>& s=intervals[i];
            if(f[1]<s[0]) ans.push_back(s);
            else if(s[0]<=f[1]) ans.back()[1]=max(f[1],s[1]);
        }
        return ans;
    }
};
// Helper function to compare two 2D vectors.
bool compareVectors(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if(a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if(a[i].size() != b[i].size()) return false;
        for (size_t j = 0; j < a[i].size(); j++) {
            if(a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// Helper function to print a 2D vector in the format: [[a,b],[c,d],...]
void printVector2D(const vector<vector<int>>& intervals) {
    cout << "[";
    for (size_t i = 0; i < intervals.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < intervals[i].size(); j++) {
            cout << intervals[i][j];
            if(j < intervals[i].size() - 1)
                cout << ",";
        }
        cout << "]";
        if(i < intervals.size() - 1)
            cout << ",";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> intervals, vector<vector<int>> expected) {
    Solution sol;
    vector<vector<int>> result = sol.merge(intervals);
    if (compareVectors(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: ";
        printVector2D(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: Expected ";
        printVector2D(expected);
        cout << " but got ";
        printVector2D(result);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    // Expected Output: [[1,6],[8,10],[15,18]]
    vector<vector<int>> intervals1 = { {1,3}, {2,6}, {8,10}, {15,18} };
    vector<vector<int>> expected1 = { {1,6}, {8,10}, {15,18} };
    runTest(1, intervals1, expected1);

    // Test Case 2:
    // Input: intervals = [[1,4],[4,5]]
    // Expected Output: [[1,5]]
    vector<vector<int>> intervals2 = { {1,4}, {4,5} };
    vector<vector<int>> expected2 = { {1,5} };
    runTest(2, intervals2, expected2);

    return 0;
}