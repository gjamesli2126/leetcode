#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Log{
public:
    enum Cmd{
        start,
        end
    };
    int prcoessID;
    int lastSeenTime;
    Cmd cmd;
    Log(const string& str){
        int firstColInd=str.find(':');
        int secondColInd=str.find(':',firstColInd+1);//pos 是在後面
        prcoessID=stoi(str.substr(0,firstColInd+1));
        if(secondColInd-firstColInd==6)cmd=start;
        else cmd=end;
        lastSeenTime=stoi(str.substr(secondColInd+1,str.length()));
    }
};
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        //雖然一個 process 會被自己的 recursive call給中斷，但是若只在乎統計該thread 執行的時間，可以繼續加總 but 若有先遇到該 thead的end要先相消(stack
        vector<int> ans(n,0);
        stack<Log> stk;
        for(string& slog:logs){
            Log log(slog);
            if(log.cmd==Log::start){
                if(!stk.empty()){
                    Log& toplog=stk.top();
                    ans[toplog.prcoessID]+=log.lastSeenTime-toplog.lastSeenTime;
                    toplog.lastSeenTime=log.lastSeenTime;
                }
                stk.push(log);
            }
            else{//end
                assert(log.prcoessID==stk.top().prcoessID);
                Log& toplog=stk.top();
                ans[log.prcoessID]+=log.lastSeenTime-toplog.lastSeenTime+1;//end 時要包含(inclusive
                stk.pop();
                if(!stk.empty()) stk.top().lastSeenTime=log.lastSeenTime+1;
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