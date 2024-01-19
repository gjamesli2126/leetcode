#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<vector<int>> ans;
    void dfs(vector<int>& remain,vector<int>& cur,vector<bool>& avail){
        if(remain.size()==cur.size()){
            ans.push_back(cur);
            return;
        }
        for(int i=0;i<remain.size();++i){
            if(!avail[i]) continue;
            int n= remain[i];
            cur.push_back(n);
//            remain.erase(remain.begin()+i);
            avail[i]=false;
            dfs(remain,cur,avail);

            cur.pop_back();
            avail[i]=true;
//            remain.insert(remain.begin()+i,n);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> mpt;
        vector<bool> avail(nums.size(),true);
        dfs(nums,mpt,avail);
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

bool compareSets(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;

    for (const auto& vec : a) {
        if (find(b.begin(), b.end(), vec) == b.end()) return false;
    }
    return true;
}
int mainTest() {
    // Define test cases and expected results
    vector<pair<vector<int>, vector<vector<int>>>> testCases = {
            {{1, 2, 3}, {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}},
            {{0, 1}, {{0, 1}, {1, 0}}},
            {{1}, {{1}}}
    };

    // Iterate through test cases and display results
    for (auto& [testCase, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        cout << "Input: ";
        printResult({testCase});
        vector<vector<int>> result = solution.permute(testCase);
        cout << "Output: ";
        printResult(result);

        // Determine pass/fail status
        bool isPass = compareSets(result, expected);
        if (isPass) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}