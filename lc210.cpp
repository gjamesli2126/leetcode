#include<bits/stdc++.h>
#define mainTest main
using namespace std;
class Solution {
private:
    enum status{
        unvisited,
        seen,
        fullyProcessed
    };
    vector<unordered_set<int>> preReqs;
    vector<int> courses;
    vector<status> visited;
    bool dfs(int course){
        if(visited[course]==seen) return false;//cycle
        else if(visited[course]==fullyProcessed) return true;
        auto& pres=preReqs[course];
        visited[course]=seen;
        for(const auto& pre:pres){
            if(!dfs(pre)) return false;
        }
        visited[course]=fullyProcessed;
        courses.emplace_back(course);
        return true;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        preReqs.resize(numCourses);
        visited.resize(numCourses);
        //build graph
        for(const auto& vec:prerequisites){
            int crs=vec[0];
            int pre=vec[1];
            preReqs[crs].insert(pre);
        }
        //traverse with topological
        for(int crs=0;crs<numCourses;++crs){
            if(!dfs(crs)) return {};
        }
        return courses;
    }
};

void printTestResult(int testNum, const vector<int>& expected, const vector<int>& actual, int& failedTests) {
    cout << "Test #" << testNum << ": ";
    if (expected == actual) {
        cout << "\033[32m" << "Passed" << "\033[0m"; // Green for passed
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m"; // Red for failed
        cout << ". Expected: [";
        for (int course : expected) {
            cout << course << ",";
        }
        cout << "], Actual: [";
        for (int course : actual) {
            cout << course << ",";
        }
        cout << "]" << endl;
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
        vector<vector<int>> prerequisites = {{1,0}};
        vector<int> expected = {0,1};
        vector<int> actual = sol.findOrder(numCourses, prerequisites);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 2
    {
        Solution sol;
        int numCourses = 4;
        vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};
        vector<int> expected = {0,2,1,3};
        vector<int> actual = sol.findOrder(numCourses, prerequisites);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Test 3
    {
        Solution sol;
        int numCourses = 1;
        vector<vector<int>> prerequisites = {};
        vector<int> expected = {0};
        vector<int> actual = sol.findOrder(numCourses, prerequisites);
        printTestResult(++totalTests, expected, actual, failedTests);
    }

    // Add more test cases here

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
