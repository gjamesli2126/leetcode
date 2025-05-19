#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    enum action{
        dig,
        sign,
        dot,
        exp
    };
    unordered_map<action,int> act_nextHop[8]={
            {{dig,1},{sign,2},{dot,3}},
            {{dig,1},{exp,5},{dot,4}},
            {{dig,1},{dot,3}},
            {{dig,4}},
            {{dig,4},{exp,5}},
            {{sign,6},{dig,7}},
            {{dig,7}},
            {{dig,7}},
    };

public:
    bool isNumber(const string& s) {
        //only stage: 1,4,7 are valid at return
        int stage=0;

        for(char c:s){
            action act;
            if(isdigit(c)) act=dig;
            else if(c=='+' || c=='-') act=sign;
            else if(tolower(c)=='e') act=exp;
            else if(c=='.') act=dot;
            else return false;
            cout<<act<<" "<<endl;
            if(!act_nextHop[stage].contains(act)) return false;
            stage=act_nextHop[stage][act];
        }
        return stage==1 || stage==4 || stage==7;
    }
};
void runTest(int testNum, string s, bool expected) {
    Solution sol;
    bool result = sol.isNumber(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: isNumber(\"" << s << "\") = "
             << (result ? "true" : "false")
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: isNumber(\"" << s << "\") = "
             << (result ? "true" : "false")
             << ", expected " << (expected ? "true" : "false")
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "0"
    // Expected Output: true
    runTest(1, "0", true);

    // Test Case 2:
    // Input: s = "e"
    // Expected Output: false
    runTest(2, "e", false);

    // Test Case 3:
    // Input: s = "."
    // Expected Output: false
    runTest(3, ".", false);

    // Additional Test Cases:

    // Valid numbers:
    runTest(4, "2", true);
    runTest(5, "0089", true);
    runTest(6, "-0.1", true);
    runTest(7, "+3.14", true);
    runTest(8, "4.", true);
    runTest(9, "-.9", true);
    runTest(10, "2e10", true);
    runTest(11, "-90E3", true);
    runTest(12, "3e+7", true);
    runTest(13, "+6e-1", true);
    runTest(14, "53.5e93", true);
    runTest(15, "-123.456e789", true);

    // Invalid numbers:
    runTest(16, "abc", false);
    runTest(17, "1a", false);
    runTest(18, "1e", false);
    runTest(19, "e3", false);
    runTest(20, "99e2.5", false);
    runTest(21, "--6", false);
    runTest(22, "-+3", false);
    runTest(23, "95a54e53", false);
    runTest(24, ".1", true);
    runTest(24, ".1.", false);
    runTest(25,"32.e-80123", true);

    return 0;
}