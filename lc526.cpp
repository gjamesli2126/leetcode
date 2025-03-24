//#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define mainTest main


class Solution {
private:
    int dfs(int thisNum,int n,vector<bool>& visited){
        if(thisNum==n+1) return 1;//if all leaves are used->must have 1 success
        int count=0;
        for(int i=1;i<=n;++i){
            if(!visited[i] && (thisNum%i==0 || i%thisNum==0)){
                visited[i]=true;
                count+= dfs(thisNum+1,n,visited);
                visited[i]=false;
            }
        }
        return count;
    }
public:
    int countArrangement(int n) {
        vector<bool> visited(n+1,false);
        return dfs(1,n,visited);
    }
};


void printResult(int result, int expected) {
    if (result == expected) {
        cout << "\033[1;32mPass\033[0m";
    } else {
        cout << "\033[1;31mFail\033[0m";
    }
    cout << " | Result: " << result << ", Expected: " << expected << endl;
}

int mainTest() {
    // Test Case 1
    {
        Solution sol1;
        int n = 1;
        int expected = 1;
        int result = sol1.countArrangement(n);
        cout << "Test Case 1: n = " << n << endl;
        printResult(result, expected);
    }

    // Test Case 2
    {
        Solution sol2;
        int n = 2;
        int expected = 2;
        int result = sol2.countArrangement(n);
        cout << "Test Case 2: n = " << n << endl;
        printResult(result, expected);
    }

    // Test Case 3
    {
        Solution sol3;
        int n = 3;
        int expected = 3;
        int result = sol3.countArrangement(n);
        cout << "Test Case 3: n = " << n << endl;
        printResult(result, expected);
    }

    // Test Case 4
    {
        Solution sol4;
        int n = 4;
        int expected = 8;
        int result = sol4.countArrangement(n);
        cout << "Test Case 4: n = " << n << endl;
        printResult(result, expected);
    }

    return 0;
}