#include <bits/stdc++.h>
using namespace std;
#define mainTest main

// ---- Your MyStack implementation goes above this line ----
class MyStack {
private:
    queue<int> q;//single q using rotate the shit
    //變成 : ---> latest,....,oldest;
public:
    MyStack() {
    }

    void push(int x) {
        q.push(x);
        int sz=q.size();
        for(int i=0;i<sz-1;i++){
            int e=q.front();
            q.pop();
            q.push(e);
        }
    }

    int pop() {
        int e=q.front();
        q.pop();
        return e;
    }

    int top() {
        return q.front();

    }

    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */


// Helper: print bool as true/false
string boolToStr(bool v) { return v ? "true" : "false"; }

// Helper: compare int or bool result
bool equalResult(const string& a, const string& b) {
    return a == b;
}

// Helper: run test
void runTest(int testNum,
             const vector<string>& ops,
             const vector<vector<int>>& vals,
             const vector<string>& expected)
{
    const string GREEN="\033[32m";
    const string RED="\033[31m";
    const string RESET="\033[0m";

    vector<string> out;
    MyStack* stk = nullptr;

    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == "MyStack") {
            stk = new MyStack();
            out.push_back("null");
        }
        else if (ops[i] == "push") {
            stk->push(vals[i][0]);
            out.push_back("null");
        }
        else if (ops[i] == "top") {
            out.push_back(to_string(stk->top()));
        }
        else if (ops[i] == "pop") {
            out.push_back(to_string(stk->pop()));
        }
        else if (ops[i] == "empty") {
            out.push_back(boolToStr(stk->empty()));
        }
    }

    // Evaluate
    bool ok = (out == expected);

    cout << (ok ? GREEN : RED)
         << "Test Case " << testNum << (ok ? " PASSED" : " FAILED")
         << RESET << endl;

    if (!ok) {
        cout << "   Expected: [ ";
        for (auto &s : expected) cout << s << " ";
        cout << "]\n   Got     : [ ";
        for (auto &s : out) cout << s << " ";
        cout << "]\n";
    }

    delete stk;
}


// ---- mainTest ----
int mainTest() {

    // Example test case from the problem:

    // Input:
    // ["MyStack", "push", "push", "top", "pop", "empty"]
    // [[], [1], [2], [], [], []]
    //
    // Output:
    // [null, null, null, 2, 2, false]

    runTest(
            1,
            {"MyStack","push","push","top","pop","empty"},
            {{},{1},{2},{},{},{}},
            {"null","null","null","2","2","false"}
    );

    // Additional custom tests

    // Test 2: push several, pop all
    runTest(
            2,
            {"MyStack","push","push","push","pop","pop","pop","empty"},
            {{},{1},{2},{3},{},{},{},{}},
            {"null","null","null","null","3","2","1","true"}
    );

    // Test 3: alternating top/pop
    runTest(
            3,
            {"MyStack","push","push","top","pop","top","empty"},
            {{},{4},{7},{},{},{},{}},
            {"null","null","null","7","7","4","false"}
    );

    return 0;
}