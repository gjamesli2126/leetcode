#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int nodeNum=static_cast<int>(edges.size());
        vector<int> parents(nodeNum+1);//ignore the 0th element
        iota(parents.begin()+1,parents.end(),1);
        for(const auto& edge:edges){
            int firstNode=edge[0];
            int secondNode=edge[1];
            //find their root
            while(parents[firstNode]!=firstNode) firstNode=parents[firstNode];
            while(parents[secondNode]!=secondNode) secondNode=parents[secondNode];
            if(firstNode==secondNode) return edge;
            else parents[secondNode]=firstNode;
        }
        return edges.back();
    }
};

void printTestResult(int testNum, const vector<int>& expected, const vector<int>& actual) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m\n"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: [" << expected[0] << "," << expected[1] << "], Actual: [" << actual[0] << "," << actual[1] << "]" << endl;
    }
}

int mainTest() {
    int testNum = 0;

    // Test case 1
    {
        Solution sol;
        vector<vector<int>> edges1 = {{1,2},{1,3},{2,3}};
        vector<int> expected1 = {2,3};
        printTestResult(++testNum, expected1, sol.findRedundantConnection(edges1));
    }

    // Test case 2
    {
        Solution sol;
        vector<vector<int>> edges2 = {{1,2},{2,3},{3,4},{1,4},{1,5}};
        vector<int> expected2 = {1,4};
        printTestResult(++testNum, expected2, sol.findRedundantConnection(edges2));
    }

    // Additional Test case 3
    {
        Solution sol;
        vector<vector<int>> edges3 = {{1,2},{3,4},{2,3},{2,4}};
        vector<int> expected3 = {2,4};
        printTestResult(++testNum, expected3, sol.findRedundantConnection(edges3));
    }

    // Additional Test case 4: More complex graph
    {
        Solution sol;
        vector<vector<int>> edges4 = {{2,7},{7,8},{3,6},{2,5},{6,8},{4,8},{2,8},{1,8},{7,10},{3,9}};
        vector<int> expected4 = {2,8}; // Adjust according to your algorithm's logic
        printTestResult(++testNum, expected4, sol.findRedundantConnection(edges4));
    }

    return 0;
}
