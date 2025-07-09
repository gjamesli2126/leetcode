#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //加 or 不加
        vector<vector<int>> output{{}};
        vector<vector<int>> tmp;
        for(int n:nums){
            tmp={};
            for(vector<int> cur:output){
                cur.push_back(n);//加 element
                tmp.push_back(cur);//把 subset加進來
                //不加那就啥都別幹
            }
            output.insert(output.end(),tmp.begin(),tmp.end());
        }
        return output;
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