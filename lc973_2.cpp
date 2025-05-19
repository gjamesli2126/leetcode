#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    static inline int calc(const vector<int>& v){
        return pow(v[0],2)+ pow(v[1],2);
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        //find k min vales ->maxheap, c++ standard
        priority_queue<pair<int,vector<int>>>maxHeap;//dist, point
        for(vector<int>& pt:points){
            maxHeap.emplace(calc(pt),pt);
            if(maxHeap.size()>k) maxHeap.pop();
        }
        vector<vector<int>> ans;
        while(!maxHeap.empty()){
            ans.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return ans;
    }
};
void runTest(int testNum, vector<vector<int>> points, int k, vector<vector<int>> expected) {
    Solution sol;
    vector<vector<int>> result = sol.kClosest(points, k);

    // Since the order of points doesn't matter, sort both results and expected outputs for comparison.
    auto cmp = [](const vector<int>& a, const vector<int>& b) {
        return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]);
    };
    sort(result.begin(), result.end(), cmp);
    sort(expected.begin(), expected.end(), cmp);

    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected: [";
        for (int i = 0; i < expected.size(); i++) {
            cout << "[" << expected[i][0] << "," << expected[i][1] << "]";
            if (i < expected.size() - 1) cout << ", ";
        }
        cout << "], Got: [";
        for (int i = 0; i < result.size(); i++) {
            cout << "[" << result[i][0] << "," << result[i][1] << "]";
            if (i < result.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: points = [[1,3],[-2,2]], k = 1
    // Expected Output: [[-2,2]]
    runTest(1, {{1,3}, {-2,2}}, 1, {{-2,2}});

    // Test Case 2:
    // Input: points = [[3,3],[5,-1],[-2,4]], k = 2
    // Expected Output: [[3,3],[-2,4]]
    runTest(2, {{3,3}, {5,-1}, {-2,4}}, 2, {{3,3}, {-2,4}});

    return 0;
}