//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define mainTest main

class TimeMap {
private:
    unordered_map<string,vector<pair<string,int>>> wholeMap; //{key: (val0,t0),(val1,t1)}
public:
    TimeMap(){
    }

    void set(const string& key, const string& value, int timestamp) {
        if(!wholeMap[key].empty() && wholeMap[key].back().second==timestamp) wholeMap[key].back().first=value;
        else wholeMap[key].emplace_back(value,timestamp);
    }

    string get(const string& key, int timestamp) {
        int l=0,r=wholeMap[key].size()-1,mid;
        string val;
        while(l<=r){
            mid=l+(r-l)/2;
            // .....<=target Find right most mid---->
            if(wholeMap[key][mid].second<=timestamp){
                l=mid+1;
                val=wholeMap[key][mid].first;
            }else r=mid-1;
        }
        return val;
    }
};

void printResult(const string& result, const string& expectedResult) {
    if (result == expectedResult) {
        cout << "\033[1;32m"; // Green color for Pass
        cout << "Pass";
    } else {
        cout << "\033[1;31m"; // Red color for Fail
        cout << "Fail";
    }
    cout << "\033[0m"; // Reset color
    cout << " Expected: \"" << expectedResult << "\", Got: \"" << result << "\"" << endl;
}

int mainTest() {
    // Test Case 1
    {
        TimeMap timeMap;
        timeMap.set("foo", "bar", 1);
        string result = timeMap.get("foo", 1);
        printResult(result, "bar");

        result = timeMap.get("foo", 3);
        printResult(result, "bar");

        timeMap.set("foo", "bar2", 4);
        result = timeMap.get("foo", 4);
        printResult(result, "bar2");

        result = timeMap.get("foo", 5);
        printResult(result, "bar2");
    }

    // Test Case 2
    {
        TimeMap timeMap;
        timeMap.set("key1", "value1", 5);
        timeMap.set("key1", "value2", 10);
        string result = timeMap.get("key1", 7);
        printResult(result, "value1");

        result = timeMap.get("key1", 10);
        printResult(result, "value2");

        result = timeMap.get("key1", 15);
        printResult(result, "value2");
    }

    // Test Case 3
    {
        TimeMap timeMap;
        string result = timeMap.get("nonexistent", 1);
        printResult(result, "");

        timeMap.set("a", "b", 100);
        result = timeMap.get("a", 99);
        printResult(result, "");

        result = timeMap.get("a", 100);
        printResult(result, "b");

        result = timeMap.get("a", 101);
        printResult(result, "b");
    }

    return 0;
}