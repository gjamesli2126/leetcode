#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string toGoatLatin(string& sentence) {
        unordered_set<char> vowal={'a','e','i','o','u'};
        string newStr;
        bool wst=true;
        char fc=0;
        for(int word=0,i=0;i<=sentence.length();i++){
            char c=sentence[i];
            if(wst){
                wst= false;
                if(!vowal.contains(tolower(c))){
                    fc=c;
                    continue;
                }
            }

            if(c==' ' || c=='\0') {
                wst=true;
                word++;
                if(fc) newStr+=fc;
                newStr+="ma";
                for(int j=0;j<word;j++) {
                    newStr+='a';
                }
                if(c==' ') newStr+=c;
                fc=0;
            }
            else newStr+=sentence[i];
        }
        return newStr;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string sentence, string expected) {
    Solution sol;
    string result = sol.toGoatLatin(sentence);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: toGoatLatin(\"" << sentence << "\") = \""
             << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: toGoatLatin(\"" << sentence << "\") = \""
             << result << "\", expected \"" << expected
             << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: sentence = "I speak Goat Latin"
    // Expected Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
    runTest(1, "I speak Goat Latin", "Imaa peaksmaaa oatGmaaaa atinLmaaaaa");

    // Test Case 2:
    // Input: sentence = "The quick brown fox jumped over the lazy dog"
    // Expected Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
    runTest(2, "The quick brown fox jumped over the lazy dog",
            "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa");

    return 0;
}