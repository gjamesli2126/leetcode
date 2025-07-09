#include <bits/stdc++.h>
#define testMain main
using namespace std;
class LOG{
public:
    int processID;
    int lastSeen;
    enum Cmd{
        start,end
    };
    Cmd cmd;
    LOG(const string& str){
        int first_column=str.find(':');
        int second_column=str.find(':',first_column+1);
        processID= stoi(str.substr(0,first_column));
        cmd=second_column-first_column==6?start:end;
        lastSeen=stoi(str.substr(second_column+1,str.length()));
    }
};
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<LOG> logstk;
        vector<int> ans(n,0);
        for(const string& slog:logs){
            LOG log(slog);

            if(log.cmd==LOG::start){
               //same OR diff process ID
               if(!logstk.empty()){
                   LOG& toplog=logstk.top();//記得要用 reference!!!!
                   ans[toplog.processID]+=log.lastSeen-toplog.lastSeen;
                   toplog.lastSeen=log.lastSeen;
               }
               logstk.push(log);
            }else{//end
                //must be same process ID
                LOG& toplog=logstk.top();//記得要用 reference!!!!
                ans[log.processID]+=log.lastSeen-toplog.lastSeen+1;//+1 becasue of in clusive
                logstk.pop();
                if(!logstk.empty()) logstk.top().lastSeen=log.lastSeen+1;//the current top log resume
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