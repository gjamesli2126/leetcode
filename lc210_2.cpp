#include<bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //create from->to table
        vector<vector<int>> from_toS(numCourses);
        //create lock(indegree) table
        vector<int> to_indgree(numCourses);

        for(const auto& this_preq:prerequisites){
            int from=this_preq[1];
            int to=this_preq[0];
            from_toS[from].emplace_back(to);
            ++to_indgree[to];
        }

        queue<int> q;
        for(int i=0;i<numCourses;i++) if(!to_indgree[i]) q.emplace(i);
        vector<int> order;
        while(!q.empty()){
            int course=q.front();
            q.pop();
            order.emplace_back(course);
            for(int to:from_toS[course]){
                --to_indgree[to];
                if(!to_indgree[to]) q.emplace(to);//meaning the course can be taken
            }
        }
        if(numCourses==order.size()) return order;
        return {};
    }
};

// ==========================================
//  ROBUST VALIDATOR FOR TOPOLOGICAL SORT
// ==========================================
bool isTopologicalSortValid(int numCourses, const vector<vector<int>>& prerequisites, const vector<int>& actual) {
    // 1. Check size (must include all courses)
    if (actual.size() != numCourses) {
        // If we expected a valid order but got empty (or vice versa), it's wrong
        // Note: This simple validator assumes a valid order IS possible for the test case.
        return false;
    }

    // 2. Check if all courses are present (Permutation check)
    unordered_map<int, int> position;
    for (int i = 0; i < actual.size(); ++i) {
        position[actual[i]] = i;
    }
    if (position.size() != numCourses) return false; // Duplicates or missing numbers

    // 3. Check Prerequisites constraints
    for (const auto& pre : prerequisites) {
        int course = pre[0];
        int dependency = pre[1];

        // Dependency must appear BEFORE the course in the order
        if (position[dependency] > position[course]) {
            return false;
        }
    }
    return true;
}

void runTest(int testNum, int numCourses, vector<vector<int>> prerequisites, int& failedTests) {
    Solution sol;
    vector<int> actual = sol.findOrder(numCourses, prerequisites);

    // We assume for these test cases a solution IS possible.
    // If the test case was meant to be impossible (cycle), we would check if actual is empty.
    bool isValid = isTopologicalSortValid(numCourses, prerequisites, actual);

    // Handle the specific case where input has a cycle (impossible)
    // For this generic test runner, let's assume if the input expected a result, valid=true.

    cout << "Test #" << testNum << ": ";
    if (isValid) {
        cout << "\033[32m" << "Passed" << "\033[0m";
        cout << " Output: [";
        for (int i=0; i<actual.size(); ++i) cout << actual[i] << (i==actual.size()-1?"":",");
        cout << "]";
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m";
        cout << " Invalid Order: [";
        for (int i=0; i<actual.size(); ++i) cout << actual[i] << (i==actual.size()-1?"":",");
        cout << "]";
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    int failedTests = 0;
    int totalTests = 0;

    // Test 1: Simple dependency
    // 注意：runTest 函數我是用 pass-by-value 接收，所以這裡直接傳 {{}} 沒問題
    runTest(++totalTests, 2, {{1,0}}, failedTests);

    // Test 2: Multiple valid paths
    runTest(++totalTests, 4, {{1,0},{2,0},{3,1},{3,2}}, failedTests);

    // Test 3: Single course
    runTest(++totalTests, 1, {}, failedTests);

    // Test 4: Cycle detection (手動測試部分)
    {
        Solution sol;
        // fix: 建立一個具名變數來存儲 vector，避開 non-const lvalue reference 錯誤
        vector<vector<int>> cycleInput = {{1,0}, {0,1}};
        vector<int> res = sol.findOrder(2, cycleInput);

        cout << "Test #" << ++totalTests << " (Cycle): ";
        if(res.empty()) cout << "\033[32m" << "Passed" << "\033[0m" << " (Correctly returned empty)" << endl;
        else { cout << "\033[31m" << "Failed" << "\033[0m" << endl; failedTests++; }
    }

    // Calculate and print error rate
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << endl << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m";
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m";
    }
    cout << endl;

    return 0;
}