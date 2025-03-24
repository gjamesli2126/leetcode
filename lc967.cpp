#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    vector<int> ans;
    int n,k;
    void dfs(int numSoFar,int numInd){
        if(numInd == n){
            ans.emplace_back(numSoFar);
            return;
        }
        int currentDigit=numSoFar%10;
        if(currentDigit-k>=0) dfs(numSoFar*10+currentDigit-k, numInd + 1);
        if(currentDigit+k<=9 && k!=0) dfs(numSoFar*10+currentDigit+k, numInd + 1);//avoid dup so condition: k!=0
    }
public:
    vector<int> numsSameConsecDiff(int n0, int k0) {
        n=n0;k=k0;
        for(int i=1;i<=9;++i) dfs(i,1);//the first digit is  1~9
        return ans;
    }
};

void printResult(const vector<int>& result, const vector<int>& expected) {
    if (result == expected) {
        cout << "\033[1;32mPass\033[0m"; // Green for Pass
    } else {
        cout << "\033[1;31mFail\033[0m"; // Red for Fail
    }

    cout << " | Result: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << result[i];
    }
    cout << "]";

    cout << " | Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << expected[i];
    }
    cout << "]" << endl;
}

int mainTest() {
    // Test Case 1
    {
        Solution sol1;
        int n = 3;
        int k = 7;
        vector<int> expected = {181, 292, 707, 818, 929}; // Example expected result

        cout << "Test Case 1:\n  Input: n = " << n << ", k = " << k << endl;

        vector<int> result = sol1.numsSameConsecDiff(n, k);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

    // Test Case 2
    {
        Solution sol2;
        int n = 2;
        int k = 1;
        vector<int> expected = {10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98}; // Example expected result

        cout << "Test Case 2:\n  Input: n = " << n << ", k = " << k << endl;

        vector<int> result = sol2.numsSameConsecDiff(n, k);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

    // Test Case 3
    {
        Solution sol3;
        int n = 2;
        int k = 0;
        vector<int> expected = {11, 22, 33, 44, 55, 66, 77, 88, 99}; // Example expected result

        cout << "Test Case 3:\n  Input: n = " << n << ", k = " << k << endl;

        vector<int> result = sol3.numsSameConsecDiff(n, k);
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "  ";
        printResult(result, expected);
    }

//    // Test Case 4
//    {
//        Solution sol4;
//        int n = 1;
//        int k = 5;
//        vector<int> expected = {0, 5}; // Example expected result
//
//        cout << "Test Case 4:\n  Input: n = " << n << ", k = " << k << endl;
//
//        vector<int> result = sol4.numsSameConsecDiff(n, k);
//        sort(result.begin(), result.end());
//        sort(expected.begin(), expected.end());
//        cout << "  ";
//        printResult(result, expected);
//    }

    return 0;
}