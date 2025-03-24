#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
public:
    string simplifyPath(const string& path) {
        vector<string> stk;
        string each_s;
        for(int i=0;i<path.length();i++){
            if(path[i]=='/') continue;
            each_s="";
            while(i<path.length() && path[i]!='/'){
                each_s+=path[i];
                i++;
            }
            if(each_s==".") continue;
            else if(each_s==".."){
                if(!stk.empty()) stk.pop_back();
            }
            else stk.push_back(each_s);
        }
        if(stk.empty()) return "/";
        string res;
        for(int i=0;i<stk.size();i++){
            res+='/'+stk[i];
        }
        return res;
    }
};

// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string input, string expected) {
    Solution sol;
    string result = sol.simplifyPath(input);
    if (result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: Input: \"" << input
             << "\" => Output: \"" << result << "\"\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: Input: \"" << input
             << "\" => Expected: \"" << expected
             << "\", Got: \"" << result << "\"\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: path = "/home/"
    // Expected Output: "/home"
    runTest(1, "/home/", "/home");

    // Example 2:
    // Input: path = "/home//foo/"
    // Expected Output: "/home/foo"
    runTest(2, "/home//foo/", "/home/foo");

    // Example 3:
    // Input: path = "/home/user/Documents/../Pictures"
    // Expected Output: "/home/user/Pictures"
    runTest(3, "/home/user/Documents/../Pictures", "/home/user/Pictures");

    // Example 4:
    // Input: path = "/../"
    // Expected Output: "/"
    runTest(4, "/../", "/");

    // Example 5:
    // Input: path = "/.../a/../b/c/../d/./"
    // Expected Output: "/.../b/d"
    runTest(5, "/.../a/../b/c/../d/./", "/.../b/d");



    return 0;
}