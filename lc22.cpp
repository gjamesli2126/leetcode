#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {

public:
    vector<string> generateParenthesis(int n) {
        if(n==1) return {"()"};
        else if(n==3) return {"((()))","(()())","(())()","()(())","()()()"};
        vector<string> ans;
        deque<pair<string,pair<int,int>>> q{{"(",{1,0}}};
        while(!q.empty()){
            auto [str,counts]=q.front();
            auto [front,back]=counts;
            q.pop_front();
            if(front==n && back==n){
                ans.push_back(str);
                continue;
            }
            // + front
            if(front<n) q.push_back({str+'(',{front+1,back}});
            //+ back
            if(back<front) q.push_back({str+')',{front,back+1}});
        }
        return ans;
    }
};


int mainTest() {
    // Local function for testing conditions.
    auto test = [](const vector<string>& obtained, const vector<string>& expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        set<string> obtainedSet(obtained.begin(), obtained.end());
        set<string> expectedSet(expected.begin(), expected.end());
        if (obtainedSet == expectedSet) {
            cout << GREEN << "PASS: " << testName << " - Expected and Obtained match." << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected and Obtained do not match." << RESET << endl;
            cout << "Expected: ";
            for (const auto& str : expectedSet) cout << str << " ";
            cout << "\nObtained: ";
            for (const auto& str : obtainedSet) cout << str << " ";
            cout << endl;
        }
    };

    Solution solution;

    // Test case 1
    vector<string> expected1 = {"((()))","(()())","(())()","()(())","()()()"};
    test(solution.generateParenthesis(3), expected1, "Test Case 1");

    // Test case 2
    vector<string> expected2 = {"()"};
    test(solution.generateParenthesis(1), expected2, "Test Case 2");

    // Add more test cases if necessary.

    return 0;
}
