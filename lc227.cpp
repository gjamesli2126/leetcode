#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    int calculate(const string &s) {
        long result=0;
        long curr_num=0;
        long last_num=0;
        char op='+';
        for(int i=0;i<s.length();i++){
            char c=s[i];
            if(isdigit(c)){
                curr_num=10*curr_num+c-'0';
            }
            if(!isdigit(c)&&!isspace(c) || i==s.length()-1){
                if(op=='+') {
                    result += last_num;
                    last_num= curr_num;
                }
                else if(op=='-'){
                    result+=last_num;
                    last_num= -curr_num;
                }
                else if(op=='*'){
                    last_num*=curr_num;
                }else if(op=='/'){
                    last_num/=curr_num;
                }
                op=c;
                curr_num=0;
            }

        }
        result+=last_num;
        return result;
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

    return 0;
}