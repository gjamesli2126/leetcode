#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<int> *v;
    vector<vector<int>> ans;
    int vSize;
    void dfsBackTracking(int i,vector<int>& cur){
        if(i==vSize){
            ans.push_back(cur);
            return;
        }
        //add
        cur.push_back((*v)[i]);
        dfsBackTracking(i+1,cur);
        cur.pop_back();
        //don't add
        while(i!=vSize-1 && (*v)[i]==(*v)[i+1]) ++i;//dedup must be after added
        dfsBackTracking(i+1,cur);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        v=&nums;
        vSize=int(nums.size());
        vector<int> cur;
        sort(nums.begin(),nums.end());
        dfsBackTracking(0, cur);
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
    vector<pair<vector<int>, vector<vector<int>>>> testCases = {
            {{1, 2, 2}, {{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}}},
            {{0}, {{}, {0}}},
            // Add more test cases as needed
    };

    for (auto& [testCase, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        vector<vector<int>> result = solution.subsetsWithDup(testCase);

        cout << "Input: ";
        printResult({testCase});

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