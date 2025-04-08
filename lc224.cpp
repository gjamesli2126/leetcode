#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    long calculate(const string& s) {
        vector<int> sign(1,1);//sign out of bracket
        long total=0;
        int curSign=1;
        for(int i=0;i<s.length();++i){
            char c=s[i];
            //if 0~9
            if(isdigit(c)){
                long num=0;
                while(i<s.length() && isdigit(s[i])) num=10*num+s[i++]-'0';
                --i;
                total+=num*sign.back()*curSign;
//                sign.pop_back();//pop for this number
            }
            //if +
//            else if (c != ' ') sign.push_back(sign.back() * (c == '-' ? -1 : 1));
            else if(c=='+') {
                curSign=1;
            }
            else if(c=='-') curSign=-1;
            else if(c=='('){
                sign.push_back(curSign*sign.back());
                curSign=1;//reset the sign for the inner number
            }
            //if )
            else if(c==')') sign.pop_back();

        }
        return total;
    }
};

void runTest(int testNum, string s, int expected) {
    Solution sol;
    long result = sol.calculate(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: calculate(\"" << s << "\") = " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: calculate(\"" << s << "\") = " << result
             << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: "1 + 1"
    // Expected Output: 2
    runTest(1, "1 + 1", 2);

    // Test Case 2:
    // Input: " 2-1 + 2 "
    // Expected Output: 3
    runTest(2, " 2-1 + 2 ", 3);

    // Test Case 3:
    // Input: "(1+(4+5+2)-3)+(6+8)"
    // Expected Output: 23
    runTest(3, "(1+(4+5+2)-3)+(6+8)", 23);

    runTest(4,"2147483647",2147483647);
    runTest(5,"1-(     -2)",3);
    runTest(6,"-(-2)+4",6);

    return 0;
}