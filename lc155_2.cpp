#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class MinStack {
private:
    stack<int> main_stack;
    stack<int> min_stack;
public:
    MinStack() {

    }

    void push(int val) {
        main_stack.push(val);
        if(min_stack.empty() || val<=min_stack.top()) min_stack.push(val);
    }

    void pop() {
        //what if pop the min val
        if(min_stack.top()==main_stack.top()) min_stack.pop();
        main_stack.pop();
    }

    int top() {
        return main_stack.top();//assuming main_stack must have val
    }

    int getMin() {
        return min_stack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
int mainTest() {
    // Local function for testing conditions.
    auto test = [](bool condition, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (condition) {
            cout << GREEN << "PASS: " << testName << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << RESET << endl;
        }
    };

    MinStack* minStack = new MinStack();

    // First test case based on the example provided.
    minStack->push(-2);
    test(minStack->getMin() == -2, "Push -2, Min is -2");

    minStack->push(0);
    test(minStack->getMin() == -2, "Push 0, Min is still -2");

    minStack->push(-3);
    test(minStack->getMin() == -3, "Push -3, Min is now -3");

    minStack->pop();
    test(minStack->top() == 0, "After popping, top is 0");
    test(minStack->getMin() == -2, "After popping, Min is -2");

    // Resetting for new test case
    delete minStack;
    minStack = new MinStack();

    // New test case from the additional input and expected output.
    minStack->push(2);
    minStack->push(0);
    minStack->push(3);
    minStack->push(0);
    test(minStack->getMin() == 0, "After multiple pushes, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 0, "After popping, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 0, "After popping, Min is 0");

    minStack->pop();
    test(minStack->getMin() == 2, "After popping, Min is 2");

    // Clean up
    delete minStack;
    return 0;
}