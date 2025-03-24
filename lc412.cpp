#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> vec(n);
        for(int i=1;i<=n;++i){
            if(i%3==0 && i%5==0) vec[i-1]="FizzBuzz";
            else if(i%3==0) vec[i-1]="Fizz";
            else if(i%5==0) vec[i-1]="Buzz";
            else vec[i-1]=to_string(i);
        }
        return vec;
    }
};

int mainTest() {
    vector<pair<int, vector<string>>> testCases = {
            {3, {"1", "2", "Fizz"}}, // Example 1
            {5, {"1", "2", "Fizz", "4", "Buzz"}}, // Example 2
            {15, {"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"}}, // Example 3
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        int input = testCases[i].first;
        vector<string> expectedOutput = testCases[i].second;

        Solution solution; // Create a new object for each test case
        vector<string> actualOutput = solution.fizzBuzz(input);

        cout << "Test " << i + 1 << ": ";
        if (actualOutput == expectedOutput) {
            cout << green << "PASS" << reset;
        } else {
            cout << red << "FAIL" << reset;
        }
        cout << " - Input: " << input << "; ";
        cout << "Expected: [";
        for (size_t j = 0; j < expectedOutput.size(); ++j) {
            if (j > 0) cout << ", ";
            cout << "\"" << expectedOutput[j] << "\"";
        }
        cout << "]; Actual: [";
        for (size_t j = 0; j < actualOutput.size(); ++j) {
            if (j > 0) cout << ", ";
            cout << "\"" << actualOutput[j] << "\"";
        }
        cout << "]\n";
    }

    return 0;
}