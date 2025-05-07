#include <bits/stdc++.h>
#define testMain main
using namespace std;
class Solution {
public:
    string simplifyPath(const string& path) {
        int len=path.size();
        int i=len-1;
        int skip=0;
        string result="";
        while(i>=0){
        //1 process trailing zero
            while(i>=0 && path[i]=='/') i--;
        //2 get the name of the folder
            int name_end_ind=i;
            while(i>=0 && path[i]!='/') i--;
            string sgmnt=path.substr(i+1,name_end_ind-i);
        //3 process the name or merge it into the result
            if(sgmnt=="." || sgmnt.empty()){}//do nothing
            else if(sgmnt=="..") skip++;
            else if(skip) skip--;//do not append sgmnt to result
            else result='/'+sgmnt+ result;

        }
        //4 result or root
        return result.empty()?"/":result;

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