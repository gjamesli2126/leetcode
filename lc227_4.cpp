#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int calculate(const string& s) {
        if(s.empty()) return 0;
        int ret=0;
        //USING istringstream is fcking EZir
        istringstream iss('+'+s);//copy where.
        char op;
        int n,last;
        while(iss>>op>>n){
            if(op=='+') ret+=n;
            else if(op=='-'){
                n=-n;
                ret+=n;
            }
            else if(op=='*') {
                n=last*n;
                ret+=-last+n;
            }
            else if(op=='/') {
                n=last/n;
                ret+=-last+n;
            }
            last=n;
        }
        return ret;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, int expected) {
    Solution sol;
    int result = sol.calculate(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: \"" << s << "\" => " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: \"" << s << "\" => Expected " << expected
             << ", Got " << result
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: s = "3+2*2"
    // Expected Output: 7
    runTest(1, "3+2*2", 7);

    // Example 2:
    // Input: s = " 3/2 "
    // Expected Output: 1
    runTest(2, " 3/2 ", 1);

    // Example 3:
    // Input: s = " 3+5 / 2 "
    // Expected Output: 5
    runTest(3, " 3+5 / 2 ", 5);

    runTest(4,"2147483647",2147483647);
    runTest(5,"12-3*4",0);
    return 0;
}