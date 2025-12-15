#include <bits/stdc++.h>
#define mainTest main
using namespace std;


class Solution {
public:
    int calculate(string s) {

    }
};


int mainTest() {
    auto printCheck = [](const string& name, int got, int expected) {
        if (got == expected) {
            cout << "\033[1;32m"; // green
            cout << "[PASS] ";
        } else {
            cout << "\033[1;31m"; // red
            cout << "[FAIL] ";
        }
        cout << "\033[0m"; // reset
        cout << name
             << " | got = " << got
             << ", expected = " << expected
             << endl;
    };

    Solution sol;

    // -------- Basic --------
    printCheck("1 + 1",
               sol.calculate("1+1"),
               2);

    printCheck("6 - 4 / 2",
               sol.calculate("6-4/2"),
               4);

    // -------- Parentheses + precedence --------
    printCheck("2*(5+5*2)/3+(6/2+8)",
               sol.calculate("2*(5+5*2)/3+(6/2+8)"),
               21);

    // -------- Nested parentheses --------
    printCheck("(1+(4+5+2)-3)+(6+8)",
               sol.calculate("(1+(4+5+2)-3)+(6+8)"),
               23);

    // -------- Multiple digits --------
    printCheck("123 + 456 * 2",
               sol.calculate("123+456*2"),
               1035);

    // -------- Division truncates toward zero --------
    printCheck("7 / 3",
               sol.calculate("7/3"),
               2);

    printCheck("14 - 3 * 4 / 2",
               sol.calculate("14-3*4/2"),
               8);

    // -------- Parentheses with division --------
    printCheck("(8+2)/(3)",
               sol.calculate("(8+2)/3"),
               3);

    // -------- Deep nesting --------
    printCheck("((2+3)*(4+5))/3",
               sol.calculate("((2+3)*(4+5))/3"),
               15);

    return 0;
}