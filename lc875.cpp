#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
private:
//    long timeCalc(const vector<int>& piles,const int& speed){
//        long totalTime=0;
//        for(const int& p:piles){
//            totalTime+= long(ceil(double(p)/double(speed)));
//        }
//        return totalTime;
//    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int mid;
        int ub=*max_element(piles.begin(),piles.end());
        int lb=1,result=ub;
        long totalTime;
        while(lb<=ub){
            mid=(lb+ub)/2;
            totalTime= accumulate(piles.begin(),piles.end(),0L,[&mid](long total,int p){
                return total+long(ceil(double(p)/double(mid)));
            });
            if(totalTime<=h){
                result=mid;// min(result,mid);
                ub=mid-1;
            }
            else lb=mid+1;
        }
        return result;
    }
};

int mainTest() {
    // Local function for testing conditions.
    auto test = [](int obtained, int expected, const string &testName) {
        const string GREEN = "\033[32m";
        const string RED = "\033[31m";
        const string RESET = "\033[0m";
        if (obtained == expected) {
            cout << GREEN << "PASS: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        } else {
            cout << RED << "FAIL: " << testName << " - Expected: " << expected << ", Obtained: " << obtained << RESET << endl;
        }
    };

    Solution solution;

    // Array of test cases
    struct TestCase {
        vector<int> piles;
        int h;
        int expected;
    };

    vector<TestCase> testCases = {
            {{3,6,7,11}, 8, 4},      // Test case 1
            {{30,11,23,4,20}, 5, 30}, // Test case 2
            {{30,11,23,4,20}, 6, 23},
            {{312884470},312884469,2},
            {{332484035,524908576,855865114,632922376,222257295,690155293,112677673,679580077,337406589,290818316,877337160,901728858,679284947,688210097,692137887,718203285,629455728,941802184},823855818,14},
            {{1000000000},2,500000000},
            {{805306368,805306368,805306368},1000000000,3}
    };

    // Iterating over test cases
    for (int i = 0; i < testCases.size(); i++) {
        int result = solution.minEatingSpeed(testCases[i].piles, testCases[i].h);
        test(result, testCases[i].expected, "Test Case " + to_string(i + 1));
    }

    return 0;
}
