//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>
#define mainTest main
using namespace std;

class Solution {
private:
    string vec_to_strIP(const vector<string>& vecip){
        string s=vecip[0];
        for(int i=1;i<vecip.size();++i){
            s+="."+vecip[i];
        }
        return s;
    }
    vector<string> get_edges(const string& orgStr,int st_ind){//between 2 dots,1 edge==1 slot
        vector<string> edges;
        for(int i=1;i<=3 && st_ind+i<=orgStr.length();++i){
            edges.emplace_back(orgStr.substr(st_ind,i));
        }
        return edges;
    }
    bool is_valid_ip_slot(const string& slot){
        if(slot.length()>1 && slot[0]=='0' || stoi(slot)>255) return false;
        return true;
    }
    void dfs(vector<string>& results,vector<string>& slots,int st_ind,const string& orgStr){
        if(slots.size()>4) return;
        if(st_ind==orgStr.length() && slots.size()==4) {
            results.emplace_back(vec_to_strIP(slots));
            return;
        }
        //for each edge
        for(const string& edge: get_edges(orgStr,st_ind)){
            //if valid slot taken

            if(!is_valid_ip_slot(edge)) continue; // not valid
            //+
            slots.emplace_back(edge);
            dfs(results,slots,st_ind+edge.length(),orgStr);
            //-
            slots.pop_back();
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> results,slots;

        dfs(results,slots,0,s);
        return results;
    }
};

void printResult(const vector<string>& result, const vector<string>& expected) {
    if (result == expected) {
        cout << "\033[1;32mCorrect\033[0m"; // Green for Correct
    } else {
        cout << "\033[1;31mWrong\033[0m"; // Red for Wrong
    }
    cout << " | Expected: [";
    for (size_t i = 0; i < expected.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << expected[i] << "\"";
    }
    cout << "] | Output: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << result[i] << "\"";
    }
    cout << "]" << endl;
}

int mainTest() {
    vector<string> result, expected;

    // Test Case 1
    Solution sol1;
    result = sol1.restoreIpAddresses("25525511135");
    expected = {"255.255.11.135", "255.255.111.35"};
    cout << "Test Case 1: ";
    printResult(result, expected);

    // Test Case 2å
    Solution sol2;
    result = sol2.restoreIpAddresses("0000");
    expected = {"0.0.0.0"};
    cout << "Test Case 2: ";
    printResult(result, expected);

    // Test Case 3
    Solution sol3;
    result = sol3.restoreIpAddresses("101023");
    expected = {"1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"};
    cout << "Test Case 3: ";
    printResult(result, expected);

    return 0;
}