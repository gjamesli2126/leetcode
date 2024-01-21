#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<int> *cans;
    vector<vector<int>> ans;

    int canSize;
    int tar;
    void dfsBackTracking(const int& target,int i,vector<int>& cur,int& sum){
        if(sum==target){
            ans.push_back(cur);
            return;
        }
        else if(sum>target || i==canSize) return;
        //add this
        cur.push_back((*cans)[i]);
        sum+=(*cans)[i];
        dfsBackTracking(target,i+1,cur,sum);
        //don't add this
        while(i!=canSize-1 && (*cans)[i]==(*cans)[i+1]) ++i;
        cur.pop_back();
        sum-=(*cans)[i];
        dfsBackTracking(target,i+1,cur,sum);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        cans=&candidates;
        canSize=static_cast<int>(candidates.size());
        vector<int> cur;
        int sum=0;
        sort(candidates.begin(),candidates.end());
        dfsBackTracking(target,0,cur,sum);
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

bool compareSets(vector<vector<int>>& a, vector<vector<int>>& b) {
    for (auto& vec : a) sort(vec.begin(), vec.end());
    for (auto& vec : b) sort(vec.begin(), vec.end());
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int mainTest() {
    vector<pair<pair<vector<int>, int>, vector<vector<int>>>> testCases = {
            {{ {10,1,2,7,6,1,5}, 8 }, {{1,1,6}, {1,2,5}, {1,7}, {2,6}}},
            {{ {2,5,2,1,2}, 5 }, {{1,2,2}, {5}}}
            // Add more test cases as needed
    };

    for (auto& [input, expected] : testCases) {
        auto& [candidates, target] = input;
        Solution solution; // Create a new Solution object for each test case
        vector<vector<int>> result = solution.combinationSum2(candidates, target);

        cout << "Input: candidates = [";
        for (size_t i = 0; i < candidates.size(); ++i) {
            cout << candidates[i];
            if (i < candidates.size() - 1) cout << ", ";
        }
        cout << "], target = " << target << "\n";

        cout << "Expected Output: ";
        printResult(expected);

        cout << "Your Output: ";
        printResult(result);

        // Determine pass/fail status
        cout << "Test Result: ";
        if (compareSets(result, expected)) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
