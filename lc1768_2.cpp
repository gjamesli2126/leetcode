#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string mergeAlternately(const string& word1,const string& word2) {
        int p1=0,p2=0;
        string s;
        while(p1<word1.length() || p2<word2.length()){
            if(p1<word1.length()) s+=word1[p1++];
            if(p2<word2.length()) s+=word2[p2++];
        }
        return s;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, const string& word1, const string& word2, const string& expected) {
    Solution sol;
    string result = sol.mergeAlternately(word1, word2);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: mergeAlternately(\"" << word1 << "\", \""
             << word2 << "\") = \"" << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: mergeAlternately(\"" << word1 << "\", \""
             << word2 << "\") = \"" << result << "\", expected \""
             << expected << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: word1 = "abc", word2 = "pqr"
    // Output: "apbqcr"
    runTest(1, "abc", "pqr", "apbqcr");

    // Example 2:
    // Input: word1 = "ab", word2 = "pqrs"
    // Output: "apbqrs"
    runTest(2, "ab", "pqrs", "apbqrs");

    // Example 3:
    // Input: word1 = "abcd", word2 = "pq"
    // Output: "apbqcd"
    runTest(3, "abcd", "pq", "apbqcd");

    return 0;
}