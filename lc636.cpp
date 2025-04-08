#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Log{
public:
    int id;
    bool isStart=false;
    int timeStamp;
    Log(const string& s){
        int colPos1=s.find(':');
        int colPos2=s.find(':',colPos1+1);
        id=stoi(s.substr(0,colPos1));
        timeStamp=stoi(s.substr(colPos2+1,(int)s.size()-1-colPos2));
        isStart=colPos2-colPos1==6;
    };
};
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        if(!n) return {};
        vector<int> ans(n);
        stack<Log> idStk;
        for(const string& s:logs){
            Log log(s);
            if(log.isStart) idStk.push(log);
            else{
                int newProcessTimeDelta=log.timeStamp-idStk.top().timeStamp+1;//end time enclusive
                ans[log.id]+=newProcessTimeDelta;
                idStk.pop();
                if(idStk.empty()) continue;
                ans[idStk.top().id]-=newProcessTimeDelta;
            }
        }

        return ans;
    }
};

// Helper function to compare two vectors for equality.
bool compareVectors(const vector<int>& a, const vector<int>& b) {
    return a == b;
}

// Helper function to print a vector.
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << (i < vec.size() - 1 ? ", " : "");
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, int n, vector<string> logs, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.exclusiveTime(n, logs);

    if (compareVectors(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: exclusiveTime(" << n << ", logs) = ";
        printVector(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: exclusiveTime(" << n << ", logs) = ";
        printVector(result);
        cout << ", expected ";
        printVector(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
    // Expected Output: [3,4]
    runTest(1, 2, {"0:start:0", "1:start:2", "1:end:5", "0:end:6"}, {3,4});

    // Test Case 2:
    // Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
    // Expected Output: [8]
    runTest(2, 1, {"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"}, {8});

    // Test Case 3:
    // Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
    // Expected Output: [7,1]
    runTest(3, 2, {"0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"}, {7,1});

    return 0;
}