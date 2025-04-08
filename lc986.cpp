#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int f,s;
        vector<vector<int>> ans;
        for(f=0,s=0;f<firstList.size() && s<secondList.size();){
            int fl=firstList[f][0];
            int fr=firstList[f][1];
            int sl=secondList[s][0];
            int sr=secondList[s][1];

            int chosen_l=(fl>sl)?fl:sl;
            int chosen_r=(fr<sr)?fr:sr;
            if(chosen_l<=chosen_r) ans.push_back({chosen_l,chosen_r});
            //f++ or s++
            if(fr<=sr) f++;
            else s++;
        }
        return ans;
    }
};

void runTest(int testNum, vector<vector<int>> firstList, vector<vector<int>> secondList, vector<vector<int>> expected) {
    Solution sol;
    vector<vector<int>> result = sol.intervalIntersection(firstList, secondList);

    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: ";
        for (auto &interval : expected) {
            cout << "[";
            for (int i = 0; i < interval.size(); i++) {
                cout << interval[i] << (i < interval.size()-1 ? "," : "");
            }
            cout << "] ";
        }
        cout << "\nGot: ";
        for (auto &interval : result) {
            cout << "[";
            for (int i = 0; i < interval.size(); i++) {
                cout << interval[i] << (i < interval.size()-1 ? "," : "");
            }
            cout << "] ";
        }
        cout << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: firstList = [[0,2],[5,10],[13,23],[24,25]],
    //        secondList = [[1,5],[8,12],[15,24],[25,26]]
    // Expected Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
    vector<vector<int>> firstList1 = {{0,2}, {5,10}, {13,23}, {24,25}};
    vector<vector<int>> secondList1 = {{1,5}, {8,12}, {15,24}, {25,26}};
    vector<vector<int>> expected1 = {{1,2}, {5,5}, {8,10}, {15,23}, {24,24}, {25,25}};
    runTest(1, firstList1, secondList1, expected1);

    // Test Case 2:
    // Input: firstList = [[1,3],[5,9]], secondList = []
    // Expected Output: []
    vector<vector<int>> firstList2 = {{1,3}, {5,9}};
    vector<vector<int>> secondList2 = {};
    vector<vector<int>> expected2 = {};
    runTest(2, firstList2, secondList2, expected2);

    return 0;
}