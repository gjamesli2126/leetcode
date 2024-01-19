#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<int> *v;
    vector<vector<int>> result;
    int len;
    void dfsBckTrk(vector<int> nums,int i){
        if(i==len) {
            result.push_back(nums);
            return;
        }
        nums.push_back((*v)[i]);
        dfsBckTrk(nums,i+1);
        nums.pop_back();
        dfsBckTrk(nums,i+1);
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        v=&nums;
        len=v->size();
        dfsBckTrk({},0);
        return result;
    }
};

void printResult(const vector<vector<int>>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int mainTest() {
    // Define test cases
    vector<vector<int>> testCases = {
            {1, 2, 3},
            {0}
    };

    // Iterate through test cases and display results
    for (auto& testCase : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input: ";
        printResult({testCase}); // Print the input array as a single subset
        vector<vector<int>> result = solution.subsets(testCase);
        cout << "Output: ";
        printResult(result);
        cout << endl;
    }

    return 0;
}