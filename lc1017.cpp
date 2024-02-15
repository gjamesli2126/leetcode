#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define mainTest main

class Solution {
public:
    string baseNeg2(int n) {
        string res;
        while(n){
            res=to_string(n&1)+res;
            n=-(n>>1);
        }
        return res==""? "0":res;
    }
};

int mainTest() {
    vector<int> testCases = {2, 3, 4, 0, 6, 23};
    vector<string> expectedOutputs = {"110", "111", "100", "0", "11010", "1101011"};

    bool allTestsPassed = true;

    for (int i = 0; i < testCases.size(); ++i) {
        Solution solution; // Create a new instance of Solution for each test case
        string actualOutput = solution.baseNeg2(testCases[i]);
        bool testPassed = actualOutput == expectedOutputs[i];

        cout << "Test " << i + 1 << ": ";
        cout << "Input: " << testCases[i] << "; ";
        cout << "Expected: " << expectedOutputs[i] << "; ";
        cout << "Actual: " << actualOutput << "; ";
        cout << "Status: " << (testPassed ? "PASS" : "FAIL") << endl;

        if (!testPassed) allTestsPassed = false;
    }

    if (allTestsPassed) {
        cout << "All tests passed!" << endl;
    } else {
        cout << "Some tests failed." << endl;
    }

    return 0;
}
