#include <bits/stdc++.h>
#define mainTest main
using namespace std;

class Solution {
private:
    int inside_parenthesis(const string& s, int& i){
        stack<int> stk;
        stk.emplace(0);
        int inner_num=0;
        char prev_sign='+';
        for(;i<s.length();i++){
            char c=s[i];
            if(c==' ' && i!=s.length()-1) continue;//萬一最後一位是 space
            if(c=='(') inner_num+=inside_parenthesis(s,++i);
            else if(isdigit(c)){
                inner_num*=10;
                inner_num+=c-'0';
            }
            if(c=='+'||c=='-'||c=='*'||c=='/' || i==s.length()-1 || c==')'){
                if(prev_sign=='+') stk.emplace(inner_num);
                else if(prev_sign=='-') stk.emplace(-inner_num);
                else if(prev_sign=='*') stk.top()*=inner_num;
                else if(prev_sign=='/') stk.top()/=inner_num;
                if(c==')') break;
                prev_sign=c;
                inner_num=0;
            }
        }
        int res=0;
        while(!stk.empty()) {res+=stk.top();stk.pop();}
        return res;
    }
public:
    int calculate(const string& s) {
        int i=0;
        return inside_parenthesis(s,i);
    }
};

// ==========================================
//               TEST FRAMEWORK
// ==========================================

struct TestCase {
    string name;
    string input;
    int expected;
};

void printResult(const string& name, int got, int expected) {
    const int WIDTH = 40;
    cout << left << setw(WIDTH) << name << " | ";
    if (got == expected) {
        cout << "\033[1;32m[PASS]\033[0m"; // Green
    } else {
        cout << "\033[1;31m[FAIL]\033[0m"; // Red
        cout << " (Expected: " << expected << ", Got: " << got << ")";
    }
    cout << endl;
}

void printProgressBar(int current, int total) {
    int barWidth = 30;
    float progress = (float)current / total;

    cout << "\r\033[1;36m["; // Cyan color start
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\033[0m";
    cout.flush();
}

int mainTest() {
    Solution sol;
    cout << "============================================" << endl;
    cout << "        Running Basic Calc III Tests        " << endl;
    cout << "============================================" << endl;

    // 1. Normal Cases
    vector<TestCase> normalTests = {
            {"Simple Addition", "1+1", 2},
            {"Simple Precedence", "6-4/2", 4}, // 6 - 2 = 4
            {"Parentheses", "2*(5+5*2)/3", 10}, // 2*(15)/3 = 30/3 = 10
            {"Nested Parentheses", "(2+6*3+5-(3*14/7+2)*5)+3", -12},
            {"Triple Nesting", "((2+3)*(4+5))/3", 15} // (5*9)/3 = 15
    };

    cout << "\n[NORMAL CASES]" << endl;
    for (const auto& t : normalTests) {
        printResult(t.name, sol.calculate(t.input), t.expected);
    }

    // 2. Corner Cases
    vector<TestCase> cornerTests = {
            {"Just a number", "42", 42},
            {"Spaces everywhere", " 3 + 5 / 2 ", 5},
            {"Starts with parenthesis", "(1+(4+5+2)-3)+(6+8)", 23},
            {"Division Truncation", "7/3", 2},
            {"Negative intermediate", "1-100", -99}
    };

    cout << "\n[CORNER CASES]" << endl;
    for (const auto& t : cornerTests) {
        printResult(t.name, sol.calculate(t.input), t.expected);
    }

    // 3. Big Data Cases
    cout << "\n[BIG DATA CASES]" << endl;

    const int NUM_BATCHES = 306;
    const int BASE_SIZE = 65; // Adjust depending on stack depth limits

    for (int b = 1; b <= NUM_BATCHES; ++b) {
        int currentSize = b * BASE_SIZE;
        string name = "Batch " + to_string(b) + " (N=" + to_string(currentSize) + ")";

        // Progress Bar for Generation (Creating "1+1+1...+1")
        string longExpr = "0";
        // Pre-reserve to speed up string construction
        longExpr.reserve(currentSize * 2 + 10);

        for(int k=0; k < currentSize; ++k) {
            longExpr += "+1";
            if (k % (currentSize/10) == 0) printProgressBar(k, currentSize);
        }
        printProgressBar(currentSize, currentSize);
        cout << " -> Running... ";

        // Execute
        // Note: Deep recursion might cause stack overflow on local machines with default stack size 
        // for very large N. Iterative solutions handle this better.
        int result = sol.calculate(longExpr);

        // Verification
        if (result == currentSize) {
            cout << "\033[1;32m[PASS]\033[0m" << endl;
        } else {
            cout << "\033[1;31m[FAIL]\033[0m (Got: " << result << ")" << endl;
        }
    }

    cout << "\nAll tests finished." << endl;
    return 0;
}