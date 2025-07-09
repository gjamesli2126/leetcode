#include <bits/stdc++.h>
using namespace std;

constexpr unsigned WINDOW_MASK= (1<<20)-1;
class Solution {
private:
    unordered_map<char,unsigned> convert{
            {'A',0b00},{'G',0b01},{'T',0b10},{'C',0b11}
    };

    unordered_set<unsigned> seen,res;
public:
    vector<string> findRepeatedDnaSequences(const string& s) {
        int sl=s.length();
        if(!sl) return {};
        vector<string> ans;
        //need to store 20bit so use a 32bit to do it
        unsigned dna10=0;
        for(int i=0;i<10;i++) dna10=dna10<<2 | convert[s[i]];
        seen.insert(dna10);
        for(int i=10;i<sl;i++){
            dna10=dna10<<2 | convert[s[i]];
            dna10&=WINDOW_MASK;
            if(seen.contains(dna10)) {
                if(!res.contains(dna10)) ans.push_back(s.substr(i-10+1,10));// +1 是因為要 exactly 10個 element,
                // 而且要從 index=1開始
                res.insert(dna10);

            }
            else seen.insert(dna10);
        }
        return ans;
    }
};

#define mainTest main

// helper to pretty-print the result
void printResult(const vector<string>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << result[i] << "\"";
    }
    cout << "]" << endl;
}

int mainTest() {
    Solution sol;

    // Example 1
    {
        string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        auto res = sol.findRepeatedDnaSequences(s);
        printResult(res);
        // expected: ["AAAAACCCCC","CCCCCAAAAA"]
    }

    // Example 2
    {
        string s = "AAAAAAAAAAAAA";
        auto res = sol.findRepeatedDnaSequences(s);
        printResult(res);
        // expected: ["AAAAAAAAAA"]
    }

    // Longer test case
    {
        string s = "ACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGT";
        auto res = sol.findRepeatedDnaSequences(s);
        printResult(res);
        // expected: overlapping 10-mers like
        // ["ACGTACGTAC","CGTACGTACG", …] each appearing multiple times
    }

    return 0;
}