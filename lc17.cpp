#include <bits/stdc++.h>
using namespace std;
#define mainTest main

#include <bits/stdc++.h>
using namespace std;
// #define mainTest main

class Solution {
private:
    vector<string> ans;
    unordered_map<char,string> namap{
            {'2',"abc"},
            {'3',"def"},
            {'4',"ghi"},
            {'5',"jkl"},
            {'6',"mno"},
            {'7',"pqrs"},
            {'8',"tuv"},
            {'9',"wxyz"}
    };
    void dfsBackTrack(const string_view& s,string&& cur,int&& i){
        if(i == s.length()){
            ans.push_back(cur);
            return;
        }

        for(const char& c:namap[s[i]]){
            dfsBackTrack(s,cur+c, i + 1);
        }

    }
public:
    vector<string> letterCombinations(string& digits) {
        if(digits.empty()) return {};
        dfsBackTrack(digits,"",0);
        return ans;
    }
};

void printResult(const vector<string>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool compareSets(vector<string>& a, vector<string>& b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int mainTest() {
    vector<pair<string, vector<string>>> testCases = {
            {"23", {"ad","ae","af","bd","be","bf","cd","ce","cf"}},
            {"", {}},
            {"2", {"a","b","c"}}
            // Add more test cases as needed
    };

    for (auto& [input, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        vector<string> result = solution.letterCombinations(input);

        cout << "Input: \"" << input << "\"\n";
        cout << "Expected Output: ";
        printResult(expected);
        cout << "Your Output: ";
        printResult(result);

        // Determine pass/fail status
        cout << "Test Result: ";
        if (compareSets(result, expected)) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}


void printResult(const vector<string>& result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool compareSets(vector<string>& a, vector<string>& b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int mainTest() {
    vector<pair<string, vector<string>>> testCases = {
            {"23", {"ad","ae","af","bd","be","bf","cd","ce","cf"}},
            {"", {}},
            {"2", {"a","b","c"}}
            // Add more test cases as needed
    };

    for (auto& [input, expected] : testCases) {
        Solution solution; // Create a new Solution object for each test case
        vector<string> result = solution.letterCombinations(input);

        cout << "Input: \"" << input << "\"\n";
        cout << "Expected Output: ";
        printResult(expected);
        cout << "Your Output: ";
        printResult(result);

        // Determine pass/fail status
        cout << "Test Result: ";
        if (compareSets(result, expected)) {
            cout << "\033[32mPass\033[0m" << endl;
        } else {
            cout << "\033[31mFail\033[0m" << endl;
        }
        cout << endl;
    }

    return 0;
}
