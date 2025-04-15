#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    string getHash(const vector<int>& vec){
        string s;
        for(int n:vec) s+=n+26;
        return s;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string,vector<string>> hash_strs;
        for(const string& s:strings){
            //extract identifier
//            int pc=s[s.length()-1];
            vector<int> id;
            for(const char c:s){
                id.push_back((c-s[0]+26)%26);
//                pc=c;
            }
            //gethash
            hash_strs[getHash(id)].push_back(s);
        }
        vector<vector<string>> ans(hash_strs.size());
        int i=0;
        for(const auto& [id,vec]:hash_strs){
            ans[i++]=vec;
        }
        return ans;
    }
};

// Helper function to sort the groups in a canonical order.
void sortGroups(vector<vector<string>>& groups) {
    // Sort each individual group lexicographically.
    for (auto& group : groups) {
        sort(group.begin(), group.end());
    }
    // Then sort the groups based on their first element.
    sort(groups.begin(), groups.end(), [](const vector<string>& a, const vector<string>& b) {
        if(a.empty() && b.empty()) return false;
        if(a.empty()) return true;
        if(b.empty()) return false;
        return a[0] < b[0];
    });
}

// Helper function to print vector of vector of strings.
void printGroups(const vector<vector<string>>& groups) {
    cout << "[";
    for (int i = 0; i < groups.size(); i++) {
        cout << "[";
        for (int j = 0; j < groups[i].size(); j++) {
            cout << groups[i][j] << (j < groups[i].size() - 1 ? ", " : "");
        }
        cout << "]";
        if(i < groups.size() - 1) cout << ", ";
    }
    cout << "]";
}

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<string> strings, vector<vector<string>> expected) {
    Solution sol;
    vector<vector<string>> result = sol.groupStrings(strings);

    // Sort both result and expected groups for comparison (order doesn't matter)
    sortGroups(result);
    sortGroups(expected);

    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: groupStrings(strings) = ";
        printGroups(result);
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: groupStrings(strings) = ";
        printGroups(result);
        cout << ", expected ";
        printGroups(expected);
        cout << "\033[0m" << endl;
    }
}

int testMain(){
    // Test Case 1:
    // Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
    // Expected Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
    vector<string> input1 = {"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"};
    vector<vector<string>> expected1 = {{"acef"}, {"a", "z"}, {"abc", "bcd", "xyz"}, {"az", "ba"}};
    runTest(1, input1, expected1);

    // Test Case 2:
    // Input: strings = ["a"]
    // Expected Output: [["a"]]
    vector<string> input2 = {"a"};
    vector<vector<string>> expected2 = {{"a"}};
    runTest(2, input2, expected2);

    return 0;
}