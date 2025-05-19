#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        //using stack. Think of and ()[]{} problem

        int top=-1;
        for(char c:s){
            if(top!=-1 && c==s[top]) top--;
            else s[++top]=c;
        }
        if(top==-1) return "";
        return s.substr(0,top+1);
    }
};

// Helper function to print a string.
void printString(const string& str) {
    cout << "\"" << str << "\"";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& input, const string& expected) {
    Solution sol;
    string result = sol.removeDuplicates(input);

    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: removeDuplicates(\"" << input << "\") = ";
        printString(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: removeDuplicates(\"" << input << "\") = ";
        printString(result);
        cout << ", expected ";
        printString(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "abbaca"
    // Expected Output: "ca"
    runTest(1, "abbaca", "ca");

    // Test Case 2:
    // Input: s = "azxxzy"
    // Expected Output: "ay"
    runTest(2, "azxxzy", "ay");

    return 0;
}