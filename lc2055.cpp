//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define mainTest main

class Solution {
private:
    int getResult(const vector<int>& candlesLoc,int q_left,int q_right){
        if(candlesLoc.empty()) return 0;
        int l=0,r=candlesLoc.size()-1,mid;
        int left_pos=-1,right_pos=-1;
        //get most valid left candle
        while(l<=r){
            mid=l+(r-l)/2;
            //<-----mid
            if(candlesLoc[mid]>=q_left){
                left_pos=mid;
                r=mid-1;
            }else l=mid+1;
        }

        l=left_pos==-1?0:left_pos;
        r=candlesLoc.size()-1;
        while(l<=r){
            mid=l+(r-l)/2;
            //---->mid
            if(candlesLoc[mid]<=q_right){
                right_pos=mid;
                l=mid+1;
            }else r=mid-1;
        }
        //get most valid right candle
        if(left_pos==-1 || right_pos==-1 || left_pos>=right_pos) return 0;//not found
        return candlesLoc[right_pos]-candlesLoc[left_pos]-1-(right_pos-left_pos-1);
    }
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        vector<int> vec,candleLoc;
        vec.reserve(queries.size());
        for(int i=0;i<s.length();++i) if(s[i]=='|') candleLoc.push_back(i);
        for(const auto& query:queries){
            vec.push_back(getResult(candleLoc,query[0],query[1]));
        }
        return vec;
    }
};

void printResult(const vector<int>& result, const vector<int>& expectedResult) {
    if (result == expectedResult) {
        cout << "\033[1;32m"; // Green color for Pass
        cout << "Pass";
    } else {
        cout << "\033[1;31m"; // Red color for Fail
        cout << "Fail";
    }
    cout << "\033[0m"; // Reset color
    cout << " Expected: [";
    for (size_t i = 0; i < expectedResult.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << expectedResult[i];
    }
    cout << "], Got: [";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << result[i];
    }
    cout << "]" << endl;
}

int mainTest() {
    string s;
    vector<vector<int>> queries;
    vector<int> expectedResult, result;

    // Test Case 1
    {
        Solution sol;
        s = "**|**|***|";
        queries = {{2, 5}, {5, 9}};
        expectedResult = {2, 3};
        result = sol.platesBetweenCandles(s, queries);
        printResult(result, expectedResult);
    }

    // Test Case 2
    {
        Solution sol;
        s = "***|**|*****|**||**|*";
        queries = {{1, 17}, {4, 5}, {14, 17}, {5, 11}, {15, 16}};
        expectedResult = {9, 0, 0, 0, 0};
        result = sol.platesBetweenCandles(s, queries);
        printResult(result, expectedResult);
    }
    // Test Case 3
    {
        Solution sol;
        s = "||*";
        queries = {{2,2}};
        expectedResult = {0};
        result = sol.platesBetweenCandles(s, queries);
        printResult(result, expectedResult);
    }
    // Test Case 4
    {
        Solution sol;
        s = "***";
        queries = {{2,2}};
        expectedResult = {0};
        result = sol.platesBetweenCandles(s, queries);
        printResult(result, expectedResult);
    }
    // Test Case 5
    {
        Solution sol;
        s = "*|*";
        queries = {{2,2}};
        expectedResult = {0};
        result = sol.platesBetweenCandles(s, queries);
        printResult(result, expectedResult);
    }
    return 0;
}