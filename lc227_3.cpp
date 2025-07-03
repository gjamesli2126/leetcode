#include <bits/stdc++.h>
#define testMain main
using namespace std;

class Solution {
private:
    inline void localOutput(char prev_sign, long& loc_num,long& region_num){
        if(prev_sign=='*') region_num*=loc_num;
        else if(prev_sign=='/') region_num/=loc_num;
        else region_num=loc_num;
        loc_num=0;
    }
    inline void regionOutput(char region_sign,long& region_num,long& ans){
        if(region_sign=='+') ans+=region_num;
        else if(region_sign=='-') ans-=region_num;
        region_num=0;
    }
public:
    int calculate(const string& s) {
        if(s.empty()) return 0;
        int sl=s.length();
        long region_num=0;
        char region_sign='+';//+-
        char prev_sign=NULL;//*/
        long loc_num=0;
        long ans=0;
        for(int i=0;i<sl;i++){
            char c=s[i];//if put i==sl then here is undef err
            if(c==' ') continue;
            if(c=='+' || c=='-'){
                localOutput(prev_sign,loc_num,region_num);
                regionOutput(region_sign,region_num,ans);
                region_sign=c;
                prev_sign=NULL;
            }
            else if(c=='*' || c=='/') {
                localOutput(prev_sign,loc_num,region_num);
                prev_sign=c;
            }
            else loc_num=10*loc_num+c-'0';
        }
        localOutput(prev_sign,loc_num,region_num);
        regionOutput(region_sign,region_num,ans);
        return ans;
    }
};
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, string s, int expected) {
    Solution sol;
    int result = sol.calculate(s);
    if(result == expected) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: \"" << s << "\" => " << result
             << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: \"" << s << "\" => Expected " << expected
             << ", Got " << result
             << "\033[0m" << endl;
    }
}

int testMain(){
    // Example 1:
    // Input: s = "3+2*2"
    // Expected Output: 7
    runTest(1, "3+2*2", 7);

    // Example 2:
    // Input: s = " 3/2 "
    // Expected Output: 1
    runTest(2, " 3/2 ", 1);

    // Example 3:
    // Input: s = " 3+5 / 2 "
    // Expected Output: 5
    runTest(3, " 3+5 / 2 ", 5);

    runTest(4,"2147483647",2147483647);

    return 0;
}