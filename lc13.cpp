#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_map<string,int> stable={
        {"IV",4},{"IX",9},
            {"XL",40},{"XC",90},{"CD",400},{"CM",900}
    };
    unordered_map<char,int> ctable={
            {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},
            {'D',500},{'M',1000}
    };
public:
    int romanToInt(const string& s) {
        // TODO: Implement the conversion from Roman numeral to integer.
        int ans=0;
        for(int i=0;i<s.length();){
            if(i+1<s.length()){
                string two=s.substr(i,2);
                if(stable.contains(two)){
                    ans+=stable[two];
                    i+=2;
                }else ans+=ctable[s[i++]];
            }else{
                ans+=ctable[s[i++]];
            }
        }
        return ans;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& s, int expected) {
    Solution sol;
    int result = sol.romanToInt(s);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: romanToInt(\"" << s << "\") = "
             << result << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: romanToInt(\"" << s << "\") = "
             << result << ", expected " << expected
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Provided Examples
    runTest(1, "III", 3);          // III = 3
    runTest(2, "LVIII", 58);       // L = 50, V = 5, III = 3
    runTest(3, "MCMXCIV", 1994);   // M = 1000, CM = 900, XC = 90, IV = 4

    // Additional Corner Cases
    runTest(4, "I", 1);                   // smallest value
    runTest(5, "IV", 4);                  // simple subtraction case
    runTest(6, "MMMCMXCIX", 3999);        // largest valid Roman numeral

    return 0;
}