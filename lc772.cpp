#include <bits/stdc++.h>
#define mainTest main
using namespace std;


class Solution {
private:
    void apply(char sign, int num, stack<int>& stk){
        int prev_num;
        if(sign=='+') stk.push(num);
        else if(sign=='-') stk.push(-num);
        else if(sign=='*') {
            prev_num=stk.top();
            stk.pop();
            stk.push(prev_num*num);
        }
        else if(sign=='/'){
            prev_num=stk.top();
            stk.pop();
            stk.push(prev_num/num);
        }
    }
    int sumStack(stack<int>& stk){
        int res=0;
        while(!stk.empty()){
            res+=stk.top();
            stk.pop();
        }
        return res;
    }
    int dfs(const string& s, int& i){
        stack<int> stk;
        char sign='+';
        long num=0;
        const int n=s.size();//we never split the string
        while(i<n){
            char c=s[i];
            if(c==' '){
                i++;
                continue;
            }
            //number
            if(isdigit(c)) num=num*10+c-'0';
            //(
            else if(c=='('){
                i++;
                num= dfs(s,i);
                continue;
            }
            //), operator, end of string
            else if(c=='+' || c=='-' || c=='*' || c=='/'){
                apply(sign,num,stk);
                sign=c;
                num=0;
            }
            //end of recurrision
            else if(c==')'){
                apply(sign,num,stk);
                i++;//skip the ")"
                return sumStack(stk);
            }
            i++;
        }
        //if naturally run to the end of string
        apply(sign,num,stk);
        return sumStack(stk);
    }
public:
    int calculate(const string& s) {
        int i=0;//index
        return dfs(s,i);
    }
};


int mainTest() {
    auto printCheck = [](const string& name, int got, int expected) {
        if (got == expected) {
            cout << "\033[1;32m"; // green
            cout << "[PASS] ";
        } else {
            cout << "\033[1;31m"; // red
            cout << "[FAIL] ";
        }
        cout << "\033[0m"; // reset
        cout << name
             << " | got = " << got
             << ", expected = " << expected
             << endl;
    };

    Solution sol;

    // -------- Basic --------
    printCheck("1 + 1",
               sol.calculate("1+1"),
               2);

    printCheck("6 - 4 / 2",
               sol.calculate("6-4/2"),
               4);

    // -------- Parentheses + precedence --------
    printCheck("2*(5+5*2)/3+(6/2+8)",
               sol.calculate("2*(5+5*2)/3+(6/2+8)"),
               21);

    // -------- Nested parentheses --------
    printCheck("(1+(4+5+2)-3)+(6+8)",
               sol.calculate("(1+(4+5+2)-3)+(6+8)"),
               23);

    // -------- Multiple digits --------
    printCheck("123 + 456 * 2",
               sol.calculate("123+456*2"),
               1035);

    // -------- Division truncates toward zero --------
    printCheck("7 / 3",
               sol.calculate("7/3"),
               2);

    printCheck("14 - 3 * 4 / 2",
               sol.calculate("14-3*4/2"),
               8);

    // -------- Parentheses with division --------
    printCheck("(8+2)/(3)",
               sol.calculate("(8+2)/3"),
               3);

    // -------- Deep nesting --------
    printCheck("((2+3)*(4+5))/3",
               sol.calculate("((2+3)*(4+5))/3"),
               15);

    return 0;
}