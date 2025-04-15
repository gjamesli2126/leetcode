#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string toGoatLatin(string& sentence) {
        unordered_set<char> vowal={'a','e','i','o','u'};
        string newStr;
        istringstream iss(sentence);
        string word;
        int ind=1;
        while(iss>>word){
            if(!vowal.contains(tolower(word[0]))) word=word.substr(1)+word[0];
            word+="ma";
            word.append(ind,'a');
            ++ind;
            if(!newStr.empty()) newStr+=' ';
            newStr+=word;
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