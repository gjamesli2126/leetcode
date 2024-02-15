#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int hexToDecSTL(const string& hexString) {
        return stoi(hexString, nullptr, 16);
    }
    int hexToDec(const string& hexString) {
        int strlen=static_cast<int>(hexString.length());
        int ans=0;
        for(const char c:hexString){
            if(c-'0'>=0 && c-'0'<=9) ans+=pow(16,--strlen)*(c-'0');
            else ans+=pow(16,--strlen)*(c-'A'+10);
        }
        return ans;
    }
};

int mainTest() {
    vector<string> testCases = {"1A", "2F", "10", "FF", "0", "ABC"};
    vector<int> expectedOutputs = {26, 47, 16, 255, 0, 2748};

    bool allTestsPassed = true;

    for (int i = 0; i < testCases.size(); ++i) {
        Solution solution; // Create a new instance of Solution for each test case
        int actualOutput = solution.hexToDec(testCases[i]);
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

int main() {
    return mainTest();
}
