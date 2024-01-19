#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<vector<int>> ans;
    int tar;
    vector<int> *can;

    void backTrack(int i,int sum,vector<int>& cur){
        if(sum==tar){
            ans.push_back(cur);
            return;
        }
        if(i==(*can).size() || sum>tar) return;

        backTrack(i+1,sum,cur);
        cur.push_back((*can)[i]);
        backTrack(i,sum+(*can)[i],cur);
        cur.pop_back();
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//        sort(candidates.begin(),candidates.end());
        can=&candidates;
        tar=target;
        vector<int> cur;
        backTrack(0,0,cur);
        return ans;
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

bool isExpectedResult(const vector<vector<int>>& result, const vector<vector<int>>& expected) {
    if (result.size() != expected.size()) return false;

    multiset<multiset<int>> resultSet, expectedSet;
    for (const auto& vec : result) {
        resultSet.insert(multiset<int>(vec.begin(), vec.end()));
    }
    for (const auto& vec : expected) {
        expectedSet.insert(multiset<int>(vec.begin(), vec.end()));
    }

    return resultSet == expectedSet;
}


int mainTest() {
    vector<pair<vector<int>, int>> testCases = {
            {{2, 3, 6, 7}, 7},
            {{2, 3, 5}, 8},
            {{2}, 1}
    };

    // Placeholder for expected results - replace with actual expected results
    vector<vector<vector<int>>> expectedResults = {
            // ... (actual expected results for each test case)
            {{2, 2, 3}, {7}},   // Expected results for first test case
            {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}},  // Expected results for second test case
            {}  // Expected results for third test case
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        Solution solution; // Create a new Solution object for each test case
        auto& [candidates, target] = testCases[i];
        cout << "Candidates: ";
        printResult({candidates});
        cout << "Target: " << target << "\n";
        vector<vector<int>> result = solution.combinationSum(candidates, target);
        cout << "Output: ";
        printResult(result);

        // Determine pass/fail status
        bool isPass = isExpectedResult(result, expectedResults[i]);
        if (isPass) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}