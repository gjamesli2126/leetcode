#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
    unordered_map<char,int> mp1,mp2;
    int matches=0;//how many charc in mp2 match mp1 in a-z
    //O(n) for time complex
public:
    bool checkInclusion(const string& s1, const string s2) {
        if(s1.size()>s2.size()) return false;
        int len1=int(s1.length());
        int len2=int(s2.length());
        //create hashmap for s1 & init hashmap for s2
        for(int i=0;i<len1;++i){
            mp1[s1[i]]++;
            mp2[s2[i]]++;
        }
        //init matches
        for(char c='a';c<='z';++c) if(mp1[c]==mp2[c]) ++matches;

        //main loop
        int bp=len1;
        int fpToDel=bp-len1;
        while(bp<len2 && matches!=26){
//            cout<<matches<<" ";
            char charOut=s2[fpToDel];
            char charIn=s2[bp];

            if(mp1[charOut]==mp2[charOut]) --matches;
            --mp2[charOut];
            if(mp1[charOut]==mp2[charOut]) ++matches;

            if(mp1[charIn]==mp2[charIn]) --matches;
            ++mp2[charIn];
            if(mp1[charIn]==mp2[charIn]) ++matches;

            ++fpToDel;
            ++bp;
        }
//        cout<<matches<<" ";
//        cout<<endl;
        return matches==26;
    }
};

int mainTest() {
    auto test = [](bool obtained, bool expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "[Pass] ";
        } else {
            cout << RED << "[Fail] ";
        }
        cout << RESET << testName << " - Expected: " << (expected ? "True" : "False") << ", Obtained: " << (obtained ? "True" : "False") << RESET << endl;
    };

    struct TestCase {
        string s1;
        string s2;
        bool expected;
    };

    vector<TestCase> testCases = {
            {"ab", "eidbaooo", true},  // Test case 1
            {"ab", "eidboaoo", false}, // Test case 2
            {"rokx","otrxvfszxroxrzdsltg",false},
            {"adc","dcda",true},
            // Add more test cases as needed
    };

    for (int i = 0; i < testCases.size(); i++) {
        Solution solution;
        bool result = solution.checkInclusion(testCases[i].s1, testCases[i].s2);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
