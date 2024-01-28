#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<int,unordered_set<int>> cpmap;
    bool dfs(unordered_set<int>& visited, int course){
        if(visited.contains(course)) return false;// re-visit again means a loop created
        if(cpmap[course].empty()) return true;//prerequisit cleared
        visited.insert(course);
        //loop thru all pre
        for(const int& pre:cpmap[course]){
            if(!dfs(visited,pre)) return false;
        }
        visited.erase(course);
        cpmap[course].clear();//prerequisit cleared
        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //create map/grpah
        for(const auto& v:prerequisites){
            int course=v[0];
            int pre=v[1];
            cpmap[course].insert(pre);
        }
        //traverse the graph with topological
        for(int course=0;course<numCourses;++course){
            unordered_set<int> visited;
            if(!dfs(visited,course)) return false;
        }
        return true;
    }
};

void printTestResult(int testNum, bool expected, bool actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: " << expected << ", Actual: " << actual << endl;
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1
    {
        Solution sol;
        int numCourses = 2;
        vector<vector<int>> prerequisites = {{1, 0}};
        bool expected = true;
        bool actual = sol.canFinish(numCourses, prerequisites);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        int numCourses = 2;
        vector<vector<int>> prerequisites = {{1, 0}, {0, 1}};
        bool expected = false;
        bool actual = sol.canFinish(numCourses, prerequisites);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m"; // Light blue for 0% error rate
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m"; // Orange for >0% error rate
    }
    cout << endl;

    return 0;
}
