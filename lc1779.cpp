#include <iostream>
#include <vector>
using namespace std;
#define mainTest main

class Solution {
public:
    int nearestValidPoint(int x0, int y0, vector<vector<int>>& points){
        int minDist=INT_MAX;
        int ind=-1;
        for(int i=0;i<points.size();++i){
            int x=points[i][0];
            int y=points[i][1];
            if(x==x0 || y==y0) {
                int dist = abs(y - y0)+abs(x-x0);
                if(dist<minDist){
                    minDist=dist;
                    ind=i;
                }
            }
        }
        return ind;
    }
};

void printTestResult(int testNum, int expected, int actual) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32mPassed\033[0m\n"; // Green for passed
    } else {
        cout << "\033[31mFailed. Expected: " << expected << ", Actual: " << actual << "\033[0m\n"; // Red for failed
    }
}


int mainTest() {
    vector<pair<pair<int, int>, vector<vector<int>>>> testCases = {
            {{3, 4}, {{1, 2}, {3, 1}, {2, 4}, {2, 3}, {4, 4}}},
            {{3, 4}, {{3, 4}}},
            {{3, 4}, {{2, 3}}}
    };
    vector<int> expectedResults = {2, 0, -1};

    for (int i = 0; i < testCases.size(); ++i) {
        Solution sol; // New object for each test case
        int actual = sol.nearestValidPoint(testCases[i].first.first, testCases[i].first.second, testCases[i].second);
        printTestResult(i + 1, expectedResults[i], actual);
    }

    return 0;
}
