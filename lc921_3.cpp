#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int minAddToMakeValid(const string& s) {
        int toL=0;
        int toR=0;
        for(char c:s){
            if(c=='(') toR++;
            else if(c==')'){
                if(toR) toR--;
                else toL++;
            }
        }
        return toR+toL;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, int expected) {
    Solution sol;
    int result = sol.minAddToMakeValid(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: minAddToMakeValid(\"" << s << "\") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: minAddToMakeValid(\"" << s << "\") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: s = "())"
    // Expected Output: 1
    runTest(1, "())", 1);

    // Test Case 2:
    // Input: s = "((("
    // Expected Output: 3
    runTest(2, "(((", 3);
    runTest(3, "()", 0);
    runTest(4, ")(", 2);
    runTest(5, ")()", 1);
    return 0;
}