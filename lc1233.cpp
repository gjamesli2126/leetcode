#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution{
public:
    vector<string> removeSubfolders(vector<string>& folder){
        vector<string> ans;
        sort(folder.begin(), folder.end());
        ans.emplace_back(folder[0]);
        for(int i=1;i<folder.size();i++){
            string lastFolder=ans.back()+'/';
            if(folder[i].compare(0,lastFolder.size(),lastFolder)){
                ans.emplace_back(folder[i]);
            }
        }
        return ans;
    }
};
/*
 * The current approach is sorting and checking prefixes — works fine for moderate input.
But if the dataset is huge or frequently updated, I’d build a Trie (prefix tree) where each path component is a node.
When inserting, if I hit a node that’s already an end folder, I skip adding deeper nodes — that naturally removes subfolders.
Finally, a DFS over the Trie collects all top-level folders efficiently.”
 * */
void printResult(const vector<string>& result, const vector<string>& expected){
    vector<string> sorted_result = result;
    vector<string> sorted_expected = expected;
    sort(sorted_result.begin(), sorted_result.end());
    sort(sorted_expected.begin(), sorted_expected.end());

    if (sorted_result == sorted_expected){
        cout << "\033[1;32mPass\033[0m Expected: [";
        for (size_t i = 0; i < expected.size(); ++i){
            if (i) cout << ", ";
            cout << expected[i];
        }
        cout << "]" << endl;
    }
    else{
        cout << "\033[1;31mFail\033[0m Expected: [";
        for (size_t i = 0; i < expected.size(); ++i){
            if (i) cout << ", ";
            cout << expected[i];
        }
        cout << "] Got: [";
        for (size_t i = 0; i < result.size(); ++i){
            if (i) cout << ", ";
            cout << result[i];
        }
        cout << "]" << endl;
    }
}

int mainTest(){
    Solution sol;

    cout << "Test 1" << endl;
    vector<string> folder1 = {"/a","/a/b","/c/d","/c/d/e","/c/f"};
    vector<string> expected1 = {"/a","/c/d","/c/f"};
    printResult(sol.removeSubfolders(folder1), expected1);

    cout << "Test 2" << endl;
    vector<string> folder2 = {"/a","/a/b/c","/a/b/d"};
    vector<string> expected2 = {"/a"};
    printResult(sol.removeSubfolders(folder2), expected2);

    cout << "Test 3" << endl;
    vector<string> folder3 = {"/a/b/c","/a/b/ca","/a/b/d"};
    vector<string> expected3 = {"/a/b/c","/a/b/ca","/a/b/d"};
    printResult(sol.removeSubfolders(folder3), expected3);

    cout << "Test 4" << endl;
    vector<string> folder4 = {"/o1/s1/c1","/o1/s1","/o1/s2/c1"};
    vector<string> expected4 = {"/o1/s1","/o1/s2/c1"};
    printResult(sol.removeSubfolders(folder4), expected4);

    return 0;
}