#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
    vector<string> ans;
    int target;
    string num0;
private:
    void recursiveSh(int stInd,long long prevOperand, long long totalSofar, const string& strSoFar){
        if(stInd==num0.length()){
            if(totalSofar==target) ans.emplace_back(strSoFar);
            return;
        }
        //leading zero: if single_digt--ok, if not single_digit do not process further
        long long parsedOperand=0;
        for(int i=stInd;i<num0.size();i++){
            //break if has leading zero
            if(i!=stInd/*if not single digit, meaning wanna process further*/&& num0[stInd]=='0'/*first element is 0*/) break;
            //prase the element
//            long long parsedOperand=stoll(num0.substr(stInd,i-stInd+1));//to slow
            parsedOperand=10*parsedOperand+num0[i]-'0';

            //if single digit && at VERY FIRST
            if(stInd==0) recursiveSh(i+1,parsedOperand,parsedOperand,strSoFar+ to_string(parsedOperand));
            else{
                //normal case, if op=+
                recursiveSh(i+1,parsedOperand,totalSofar+parsedOperand,strSoFar+'+'+ to_string(parsedOperand));
                //normal case, if op=-
                recursiveSh(i+1,-parsedOperand,totalSofar-parsedOperand,strSoFar+'-'+to_string(parsedOperand));
                //normal case, if op=*
                recursiveSh(i+1,prevOperand*parsedOperand,totalSofar-prevOperand+prevOperand*parsedOperand,strSoFar+'*'+to_string(parsedOperand));
                //normal case, if no-op
                    //do nothing let i++
            }

        }

    }
public:
    vector<string> addOperators(string num, int target) {
        this->target=target;
        num0=num;
        recursiveSh(0,0,0,"");
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