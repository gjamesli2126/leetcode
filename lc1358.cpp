#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Solution {
public:
    int numberOfSubstrings(string s) {
        unordered_map<char,int> count;
        int fp,bp,res=0,len=int(s.length());
        for(fp=0,bp=0;bp<len;++bp){
            ++count[s[bp]];
            while(count.size()==3){//a b c
                --count[s[fp]];
                if(!count[s[fp]]) count.erase(s[fp]);
                ++fp;
            }
            res+=fp;// if abc is valid then xxxxabc is valid too
        }
        return res;
    }
};


int mainTest() {
    Solution solution; // Create an instance of the Solution class
    // Test Case 1
    string test1 = "abcabc";
    cout << "Test Case 1 - Expected: 10, Actual: " << solution.numberOfSubstrings(test1) << endl;
    // Test Case 2
    string test2 = "aaacb";
    cout << "Test Case 2 - Expected: 3, Actual: " << solution.numberOfSubstrings(test2) << endl;
    // Test Case 3
    string test3 = "abc";
    cout << "Test Case 3 - Expected: 1, Actual: " << solution.numberOfSubstrings(test3) << endl;
    return 0;
}