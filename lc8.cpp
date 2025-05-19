#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int myAtoi(const string& s) {
        //skipping leading white, if end_of_number & see other non-difit->terminate
        int n=0;
        bool neg=false;
        //remove the damn leading whitespace
        int i=0;
        while(s[i]==' ') i++;//do not use while(s[i++]==' '){} as it will make i++ unconditionally
        //deal with sign
        if(i<s.length() && (s[i]=='-' || s[i]=='+')) neg=s[i++]=='-';

        for(;i<s.length();i++){
            char c=s[i];
            if(!isdigit(c)) return neg?-n:n;
            int dig=c-'0';
            //dealing with large number
            if(n>(INT_MAX-dig)/10) return neg?INT_MIN:INT_MAX;//n=10*n+digit 的反過來
            n=10*n+dig;
        }
        return neg?-n:n;
    }
};

void printString(const string& str) {
    cout << "\"" << str << "\"";
}

void runTest(int testNum, const string& s, int expected) {
    Solution sol;
    int result = sol.myAtoi(s);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: myAtoi(";
        printString(s);
        cout << ") = " << result << "\033[0m\n";
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: myAtoi(";
        printString(s);
        cout << ") = " << result
             << ", expected " << expected
             << "\033[0m\n";
    }
}

int testMain() {
    // Example 1:
    // Input: "42" -> 42
    runTest(1, "42", 42);
    // Example 2:
    // Input: "   -042" -> -42
    runTest(2, "   -042", -42);
    // Example 3:
    // Input: "1337c0d3" -> 1337
    runTest(3, "1337c0d3", 1337);
    // Example 4:
    // Input: "0-1" -> 0
    runTest(4, "0-1", 0);
    // Example 5:
    // Input: "words and 987" -> 0
    runTest(5, "words and 987", 0);
    runTest(6,"-91283472332",-2147483648);
    runTest(7,"21474836460",2147483647);

    return 0;
}