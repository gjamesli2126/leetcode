#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
#define mainTest main

class Solution {
public:
    int balancedString(string s) {
        int len=int(s.length());
        int fp,bp;
        int k=len/4;
        int res=len;
        unordered_map<char,int> count;
        for(const char& c:s) ++count[c];
        for(fp=0,bp=0;bp<len;++bp){
            --count[s[bp]];
            //當fp & bp交錯時，表示 bp=n-1 且未找到 故能進得來這個while loop fp 怎麼樣都無法超越bp
            //fp超越bp表示原本string 已經平衡
//            cout<<"場外     "<<fp<<bp<<res<<endl;
            while(count['Q']<=k && count['R']<=k && count['E']<=k && count['W']<=k){
//                cout<<"內先"<<count['Q']<< count['R']<< count['E']<< count['W']<<" "<<fp<<bp<<res<<endl;
                if(fp>bp) return 0;
                res=min(res,bp-fp+1);//能進來表示已經符合平衡條件
                ++count[s[fp]];//放棄使用此char -> 即為不扣此char在count_map中的frequency
                ++fp;//既然要放棄此char, 則 fp需要++-> move on to the next one
//                cout<<"內後"<<count['Q']<< count['R']<< count['E']<< count['W']<<" "<<fp<<bp<<res<<endl;
            }
//            cout<<endl;
        }
        return res;
    }
};

int mainTest() {
    // Test Cases
    string testCases[] = {
            "QWER",             // Already balanced
            "QQER",             // All same character
//            "WWEQERQWQWWRWWERQWEQ",     // Multiple replacements needed
            // ... More test cases ...
    };

    int expectedOutputs[] = {0,
                             1,
//                             4
    };

    // Set width for each field
    const int widthTestNum = 6;
    const int widthExpected = 10;
    const int widthActual = 10;
    const int widthStatus = 6;

    cout << left << setw(widthTestNum) << "Test"
         << setw(widthExpected) << "Expected"
         << ", " << setw(widthActual) << "Actual"
         << ", " << "Status:" << endl;

    for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); ++i) {
        Solution solution; // Create a new Solution object for each test case
        int actual = solution.balancedString(testCases[i]);
        bool status = (actual == expectedOutputs[i]);

        cout << setw(widthTestNum) << i+1  // Test case number
             << setw(widthExpected) << expectedOutputs[i]
             << ", " << setw(widthActual) << actual
             << ", " << (status ? "True" : "False") << endl;
    }
    return 0;
}
