#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string addBinary(const string& a,const string& b) {
        string ans;
        int A=a.length();
        int B=b.length();
        int dig=0;
        for(int i=A-1,j=B-1;i>=0 || j>=0 || dig;i--,j--){
            if(i>=0) dig+=a[i]-'0';
            if(j>=0) dig+=b[j]-'0';
            ans+=dig%2+'0';
            dig/=2;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

void runTest(int testNum, const string& a, const string& b, const string& expected) {
    Solution sol;
    string result = sol.addBinary(a, b);
    const string GREEN = "\033[32m", RED = "\033[31m", RESET = "\033[0m";
    if (result == expected) {
        cout << GREEN << "Test Case " << testNum
             << " Passed: addBinary(\"" << a << "\", \"" << b << "\") = \""
             << result << "\"" << RESET << endl;
    } else {
        cout << RED << "Test Case " << testNum
             << " Failed: addBinary(\"" << a << "\", \"" << b << "\") = \""
             << result << "\", expected \"" << expected << "\"" << RESET << endl;
    }
}

int testMain() {
    // Example 1:
    // a = "11", b = "1" -> "100"
    runTest(1, "11", "1", "100");

    // Example 2:
    // a = "1010", b = "1011" -> "10101"
    runTest(2, "1010", "1011", "10101");

    // Additional tests
    runTest(3, "0", "0", "0");
    runTest(4, "1111", "1", "10000");
    runTest(5, "100", "110010", "110110");

    return 0;
}