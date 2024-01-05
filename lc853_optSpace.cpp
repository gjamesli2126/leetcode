#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int len=int(position.size());
        vector<pair<int,int>> cars;//position, speed
        for(int i=0;i<len;++i) cars.push_back({position[i],speed[i]});
        sort(cars.begin(),cars.end());
//        stack<pair<int,float>> stk;//index_of_car vs time_to_target
        int fleet=1;
        float lastTtt=float(target-cars[len-1].first)/float(cars[len-1].second);//last time to target

        for(int i=len-2;i>=0;--i){
            float t=float(target-cars[i].first)/float(cars[i].second);
            if(t<=lastTtt) continue;
            lastTtt=t;
            ++fleet;
        }
        return fleet;
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

    // Test case 1
    int target1 = 12;
    vector<int> position1 = {10,8,0,5,3};
    vector<int> speed1 = {2,4,1,1,3};
    test(solution.carFleet(target1, position1, speed1), 3, "Test Case 1");

    // Test case 2
    int target2 = 10;
    vector<int> position2 = {3};
    vector<int> speed2 = {3};
    test(solution.carFleet(target2, position2, speed2), 1, "Test Case 2");

    // Test case 3
    int target3 = 100;
    vector<int> position3 = {0,2,4};
    vector<int> speed3 = {4,2,1};
    test(solution.carFleet(target3, position3, speed3), 1, "Test Case 3");

    // Add more test cases if necessary.
    int target4=10;
    vector<int> position4 = {6,8};
    vector<int> speed4 = {3,2};
    test(solution.carFleet(target4, position4, speed4), 2, "Test Case 4");

    // Add more test cases if necessary.
    int target=10;
    vector<int> position = {0,4,2};
    vector<int> speed = {2,1,3};
    test(solution.carFleet(target, position, speed), 1, "Test Case 5");

    return 0;
}
