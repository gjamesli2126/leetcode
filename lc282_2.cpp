#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    vector<string> ans;
    void recursiveSh(int stInd,const string& num,long long target,long long prevOperand,long long totSoFar,string strSoFar){
        if(stInd==num.length() && totSoFar==target){
            ans.push_back(strSoFar);
            return;
        }
        long long parsedOperand=0;
        string numStr;
        for(int i=stInd;i<num.length();i++){
            //if single 0 is ok, but leading 0 is not ok
            if(i>stInd && num[stInd]=='0') break;//and digit with leading 0 is invalid
            parsedOperand=10*parsedOperand+num[i]-'0';
            //if at the very very first digit in the whole num
            numStr+=num[i];
            if(stInd==0) recursiveSh(i+1,num,target,parsedOperand,parsedOperand, to_string(parsedOperand));
            else {
                recursiveSh(i + 1, num, target, parsedOperand, totSoFar + parsedOperand,
                            strSoFar + '+' + numStr);//+
                recursiveSh(i + 1, num, target, -parsedOperand, totSoFar - parsedOperand,
                            strSoFar + '-' + numStr);//-
                recursiveSh(i + 1, num, target, prevOperand * parsedOperand,
                            totSoFar - prevOperand + prevOperand * parsedOperand,
                            strSoFar + '*' + numStr);//*
            }
        }
    }
public:
    vector<string> addOperators(const string& num, long long target) {
        recursiveSh(0,num,target,0,0,"");
        return ans;
    }
};

// Helper function to sort and compare two vectors of strings
bool compareResult(vector<string> result, vector<string> expected) {
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());
    return result == expected;
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string num, int target, vector<string> expected) {
    Solution sol;
    vector<string> result = sol.addOperators(num, target);
    if (compareResult(result, expected)) {
        cout << "\033[1;32mTest Case " << testNum << " Passed: addOperators(\"" << num << "\", " << target << ") = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size()-1)
                cout << ", ";
        }
        cout << "]\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed: addOperators(\"" << num << "\", " << target << ") = [";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size()-1)
                cout << ", ";
        }
        cout << "], expected [";
        for (int i = 0; i < expected.size(); i++) {
            cout << expected[i];
            if (i < expected.size()-1)
                cout << ", ";
        }
        cout << "]\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: num = "123", target = 6
    // Expected Output: ["1*2*3", "1+2+3"]
    runTest(1, "123", 6, {"1*2*3", "1+2+3"});

    // Test Case 2:
    // Input: num = "232", target = 8
    // Expected Output: ["2*3+2", "2+3*2"]
    runTest(2, "232", 8, {"2*3+2", "2+3*2"});

    // Test Case 3:
    // Input: num = "3456237490", target = 9191
    // Expected Output: []
    runTest(3, "3456237490", 9191, {});


    runTest(4,"123456789",45,{"1*2*3*4*5-6-78+9","1*2*3*4+5+6-7+8+9","1*2*3+4+5+6+7+8+9","1*2*3+4+5-6*7+8*9","1*2*3+4-5*6+7*8+9","1*2*3+4-5*6-7+8*9","1*2*3-4*5+6*7+8+9","1*2*3-4*5-6+7*8+9","1*2*3-4*5-6-7+8*9","1*2*3-45+67+8+9","1*2*34+56-7-8*9","1*2*34-5+6-7-8-9","1*2+3*4-56+78+9","1*2+3+4+5*6+7+8-9","1*2+3+4-5+6*7+8-9","1*2+3+4-5-6+7*8-9","1*2+3+45+67-8*9","1*2+3-45+6+7+8*9","1*2+34+5-6-7+8+9","1*2+34+56-7*8+9","1*2+34-5+6+7-8+9","1*2+34-56+7*8+9","1*2+34-56-7+8*9","1*2-3*4+5+67-8-9","1*2-3+4-5-6*7+89","1*2-3-4*5+67+8-9","1*2-3-4+56-7-8+9","1*2-34+5*6+7*8-9","1*23+4*5-6+7-8+9","1*23-4-56-7+89","1+2*3*4*5+6+7-89","1+2*3*4+5*6+7-8-9","1+2*3*4-5+6*7-8-9","1+2*3+4*5*6+7-89","1+2*3+4*5-6+7+8+9","1+2*3-4-5-6*7+89","1+2*34-5*6+7+8-9","1+2+3*4*5+6-7-8-9","1+2+3*4+5+6*7-8-9","1+2+3*45-6-78-9","1+2+3+4+5+6+7+8+9","1+2+3+4+5-6*7+8*9","1+2+3+4-5*6+7*8+9","1+2+3+4-5*6-7+8*9","1+2+3-4*5+6*7+8+9","1+2+3-4*5-6+7*8+9","1+2+3-4*5-6-7+8*9","1+2+3-45+67+8+9","1+2-3*4*5+6+7+89","1+2-3*4+5*6+7+8+9","1+2-3*4-5+6*7+8+9","1+2-3*4-5-6+7*8+9","1+2-3*4-5-6-7+8*9","1+2-3+4*5+6*7-8-9","1+2-3+45+6-7-8+9","1+2-3+45-6+7+8-9","1+2-3-4-5*6+7+8*9","1+2-3-45-6+7+89","1+2-34+5+6+7*8+9","1+2-34+5+6-7+8*9","1+2-34-5-6+78+9","1+23*4+5-6-7*8+9","1+23*4-5-6*7+8-9","1+23*4-56+7-8+9","1+23+4+5+6+7+8-9","1+23+4-5*6+7*8-9","1+23+4-5-67+89","1+23-4*5+6*7+8-9","1+23-4*5-6+7*8-9","1+23-4-5+6+7+8+9","1+23-4-5-6*7+8*9","1+23-45+67+8-9","1-2*3*4+5-6+78-9","1-2*3*4-5-6+7+8*9","1-2*3+4*5+6+7+8+9","1-2*3+4*5-6*7+8*9","1-2*3+4+5+6*7+8-9","1-2*3+4+5-6+7*8-9","1-2*3+4+56+7-8-9","1-2*3+45-67+8*9","1-2*3-4+5*6+7+8+9","1-2*3-4-5+6*7+8+9","1-2*3-4-5-6+7*8+9","1-2*3-4-5-6-7+8*9","1-2*34+5*6-7+89","1-2+3*4*5-6-7+8-9","1-2+3+4-5*6+78-9","1-2+3+45+6-7+8-9","1-2+3-4*5-6+78-9","1-2+3-45+6-7+89","1-2-3*4+5+6+7*8-9","1-2-3*4-5-6+78-9","1-2-3+4-5+67-8-9","1-2-3+45-6-7+8+9","1-2-34+5+6+78-9","1-2-34+56+7+8+9","1-2-34-5+6+7+8*9","1-23*4+5+6*7+89","1-23+4*5-6*7+89","1-23+4-5+67-8+9","1-23+45-67+89","1-23-4+5+67+8-9","1-23-4-5-6-7+89","12*3*4-5*6-78+9","12*3+4+5+6-7-8+9","12*3+4+5-6+7+8-9","12*3-4-5-6+7+8+9","12*3-4-56+78-9","12+3*4+5+6-7+8+9","12+3*45-6-7-89","12+3+4-56-7+89","12+3-4*5+67-8-9","12+3-45+6+78-9","12+34-5-6-7+8+9","12-3*4*5+6+78+9","12-3*4-5+67-8-9","12-3+4*5+6-7+8+9","12-3+4+56-7-8-9","12-3-4+5*6-7+8+9","12-3-4-56+7+89","12-3-45-6+78+9"});
    return 0;
}