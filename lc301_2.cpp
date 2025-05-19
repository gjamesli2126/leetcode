#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    unordered_set<string> ans;
    void backgrackDFS(const string& s,string strSoFar,int balance,int ind,int lrem,int rrem){
        if(ind==s.length()){
            if(!balance && !lrem && !rrem) ans.insert(strSoFar);
            return;
        }
        //not add
        if(!isalpha(s[ind])){
            if(s[ind]=='(' && lrem) backgrackDFS(s,strSoFar,balance,ind+1, lrem-1,rrem);
            if(s[ind]==')' && rrem) backgrackDFS(s,strSoFar,balance,ind+1,lrem,rrem-1);
        }
        //add
        if(s[ind]=='(') backgrackDFS(s,strSoFar+s[ind],balance+1,ind+1,lrem,rrem);
        else if(s[ind]==')' && balance>0) backgrackDFS(s,strSoFar+s[ind],balance-1,ind+1,lrem,rrem);
        else if(isalpha(s[ind])) backgrackDFS(s,strSoFar+s[ind],balance,ind+1,lrem,rrem);
    }
public:
    vector<string> removeInvalidParentheses(const string& s) {
        //pre-compute if what is the min (,) too del
        int lrem=0,rrem=0;
        for(char c:s){
            if(c=='(') lrem++;
            else if(c==')'){
                if(lrem>0) lrem--;
                else ++rrem;
            }
        }
        //using backtracking( to remove OR not to remove)
        backgrackDFS(s,"",0,0,lrem,rrem);
        //may have dup!!!! so dedup
        vector<string> ans_vec(ans.begin(),ans.end());

        return ans_vec;
    }
};

void printVector(const vector<string>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "\"" << vec[i] << "\"" << (i + 1 < vec.size() ? ", " : "");
    }
    cout << "]";
}

void runTest(int testNum, const string& s, vector<string> expected) {
    Solution sol;
    vector<string> result = sol.removeInvalidParentheses(s);
    // Since order does not matter, sort both lists
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    sort(expected.begin(), expected.end());
    expected.erase(unique(expected.begin(), expected.end()), expected.end());

    const string GREEN = "\033[32m", RED = "\033[31m", RESET = "\033[0m";
    cout << "Test Case " << testNum << ": removeInvalidParentheses(\"" << s << "\") = ";
    printVector(result);
    if (result == expected) {
        cout << " " << GREEN << "PASS" << RESET << "\n";
    } else {
        cout << " " << RED << "FAIL\n";
        cout << "  Expected: ";
        printVector(expected);
        cout << RESET << "\n";
    }
}

int testMain() {
    // Example 1
    runTest(1, "()())()", {"(())()", "()()()"});
    // Example 2
    runTest(2, "(a)())()", {"(a())()", "(a)()()"});
    // Example 3
    runTest(3, ")(", {""});
    return 0;
}