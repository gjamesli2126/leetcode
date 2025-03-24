#include <bits/stdc++.h>
using namespace std;
#define mainTest main

class ParkingSystem {
private:
    int big;
    int medium;
    int small;
public:
    ParkingSystem(int big0, int medium0, int small0) {
        big=big0;
        medium=medium0;
        small=small0;
    }

    bool addCar(int carType) {
        switch (carType) {
            case 1:
                if(big>0){
                    --big;
                    return true;
                }else return false;
                break;
            case 2:
                if(medium>0){
                    --medium;
                    return true;
                }else return false;
                break;
            case 3:
                if(small>0){
                    --small;
                    return true;
                }else return false;
                break;
            default:
                return false;
        }
    }
};

int mainTest() {
    vector<tuple<vector<int>, vector<int>, vector<bool>>> testCases = {
            // Each test case: {initial slots, car types to add, expected results}
            {{1, 1, 0}, {1, 2, 3, 1}, {true, true, false, false}}, // Example 1
            {{2, 2, 2}, {1, 1, 2, 3, 3}, {true, true, true, true, true}}, // Example 2
            {{0, 0, 0}, {1, 2, 3}, {false, false, false}} // Example 3
    };

    string red = "\033[31m";
    string green = "\033[32m";
    string reset = "\033[0m";

    for (int i = 0; i < testCases.size(); ++i) {
        vector<int> initialSlots = get<0>(testCases[i]);
        vector<int> carTypes = get<1>(testCases[i]);
        vector<bool> expectedResults = get<2>(testCases[i]);

        // Create a new ParkingSystem object for the current test case
        ParkingSystem* parkingSystem = new ParkingSystem(
                initialSlots[0], initialSlots[1], initialSlots[2]
        );

        cout << "Test " << i + 1 << ":\n";

        for (int j = 0; j < carTypes.size(); ++j) {
            bool actualResult = parkingSystem->addCar(carTypes[j]);
            bool expectedResult = expectedResults[j];

            cout << "  Add car type " << carTypes[j] << ": ";
            if (actualResult == expectedResult) {
                cout << green << "PASS" << reset;
            } else {
                cout << red << "FAIL" << reset;
            }
            cout << " (Expected: " << (expectedResult ? "true" : "false")
                 << ", Actual: " << (actualResult ? "true" : "false") << ")\n";
        }

        delete parkingSystem; // Clean up
    }

    return 0;
}