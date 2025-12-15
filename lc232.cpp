#include <bits/stdc++.h>
#define testMain main
using namespace std;

// ------------------------
// Write your MyQueue here
// ------------------------
class MyQueue {
    //using 2 stacks: in-stack + out-stack
    stack<int> in_stack,out_stack;
public:
    MyQueue() {

    }

    void push(int x) {
        in_stack.push(x);
    }

    int pop() {
        if(!out_stack.empty()) {
            int e = out_stack.top();
            out_stack.pop();
            return e;
        }
       while(in_stack.size()>1) {
           out_stack.push(in_stack.top());
           in_stack.pop();
       }
        int e=in_stack.top();
        in_stack.pop();
        return e;
    }

    int peek() {
        if(!out_stack.empty()) return out_stack.top();
        while(!in_stack.empty()){
            out_stack.push(in_stack.top());
            in_stack.pop();
        }
        return out_stack.top();
    }

    bool empty() {
        return in_stack.empty() && out_stack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// -------------------------------------
// Helper functions for test formatting
// -------------------------------------
void printVector(const vector<string>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1) cout << ", ";
    }
    cout << "]";
}

bool compare(const vector<string>& a, const vector<string>& b) {
    return a == b;
}

// -------------------------------------

int testMain() {
    const string GREEN="\033[32m", RED="\033[31m", RESET="\033[0m";

    // Test Case 1 (LeetCode Example)
    vector<string> ops   = {"MyQueue", "push", "push", "peek", "pop", "empty"};
    vector<vector<int>> vals = {{}, {1}, {2}, {}, {}, {}};
    vector<string> expected   = {"null", "null", "null", "1", "1", "false"};

    vector<string> output;
    MyQueue* q = nullptr;

    for (int i = 0; i < ops.size(); i++) {
        if (ops[i] == "MyQueue") {
            q = new MyQueue();
            output.push_back("null");
        }
        else if (ops[i] == "push") {
            q->push(vals[i][0]);
            output.push_back("null");
        }
        else if (ops[i] == "peek") {
            output.push_back(to_string(q->peek()));
        }
        else if (ops[i] == "pop") {
            output.push_back(to_string(q->pop()));
        }
        else if (ops[i] == "empty") {
            output.push_back(q->empty() ? "true" : "false");
        }
    }

    if (compare(output, expected)) {
        cout << GREEN << "Test Case 1 PASSED: ";
    } else {
        cout << RED << "Test Case 1 FAILED\nExpected: ";
        printVector(expected);
        cout << "\nGot:      ";
        printVector(output);
        cout << RESET << "\n";
        return 0;
    }

    printVector(output);
    cout << RESET << endl;

    return 0;
}