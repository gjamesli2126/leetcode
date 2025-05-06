#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string addStrings(const string& num1,const string& num2) {
        int i=num1.size()-1;
        int j=num2.size()-1;
        int carry=0;
        string res;
        while(i>=0 || j>=0 || carry){
            int d1=i>=0?num1[i--]-'0':0;
            int d2=j>=0?num2[j--]-'0':0;
            int sum=carry+d1+d2;
            carry=sum/10;//?1:0;
            res+=sum%10+'0';
        }
        reverse(res.begin(),res.end());
        return res;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& num1, const string& num2, const string& expected) {
    Solution sol;
    string result = sol.addStrings(num1, num2);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: addStrings(\"" << num1 << "\", \"" << num2
             << "\") = \"" << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: addStrings(\"" << num1 << "\", \"" << num2
             << "\") = \"" << result << "\", expected \"" << expected
             << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // num1 = "11", num2 = "123" -> "134"
    runTest(1, "11", "123", "134");
    // Example 2:
    // num1 = "456", num2 = "77" -> "533"
    runTest(2, "456", "77", "533");
    // Example 3:
    // num1 = "0", num2 = "0" -> "0"
    runTest(3, "0", "0", "0");
    return 0;
}