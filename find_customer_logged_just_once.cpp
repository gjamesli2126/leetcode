#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION
// ==========================================
class Solution {
private:
    unordered_set<string> multiTimeSet;
    unordered_map<string,list<string>::iterator> oneTimeMap;
    list<string> oneTimeList;
public:
    // This method will be called every time a user logs in
    void newUserLogin(const string& username) {
        if(multiTimeSet.contains(username)) return;
        auto it=oneTimeMap.find(username);
        if(it!=oneTimeMap.end()){
            multiTimeSet.emplace(username);
            oneTimeList.erase(it->second);
            oneTimeMap.erase(username);
        }else{
            oneTimeList.push_front(username);
            oneTimeMap[username]=oneTimeList.begin();
        }
    }

    // This method will return the username of the oldest customer 
    // who has visited the website only once.
    // Return "" if no such user exists.
    string getOldestOneTimeVisitingUser() {
        return oneTimeList.back();
    }
};

// ==========================================
//  STRESS TEST INFRASTRUCTURE
// ==========================================

// Reference implementation (Ground Truth) to verify correctness
class ReferenceSolution {
private:
    unordered_map<string, int> counts;
    vector<string> first_appearance_order; // Keeps track of order
public:
    void newUserLogin(string username) {
        if (counts.find(username) == counts.end()) {
            first_appearance_order.push_back(username);
        }
        counts[username]++;
    }

    string getOldestOneTimeVisitingUser() {
        for (const string& user : first_appearance_order) {
            if (counts[user] == 1) {
                return user;
            }
        }
        return "";
    }
};

// Helper to generate random usernames
string getRandomUser(int range) {
    return "User_" + to_string(rand() % range);
}

void printProgressBar(int current, int total) {
    int barWidth = 40;
    float progress = (float)current / total;
    cout << "\rProgress: [";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %";
    cout.flush();
}

// ==========================================
//  TEST RUNNERS
// ==========================================

void runManualTestCase(int testNum, string testName,
                       const vector<string>& actions,
                       const vector<string>& expected_outputs,
                       int& failedTests) {
    Solution sol;
    int checkIndex = 0;
    bool passed = true;
    string errorMsg = "";

    for (const string& action : actions) {
        if (action.rfind("login:", 0) == 0) {
            // Action is a login: "login:john"
            string name = action.substr(6);
            sol.newUserLogin(name);
        } else if (action == "get") {
            // Action is a query
            string result = sol.getOldestOneTimeVisitingUser();
            string expected = expected_outputs[checkIndex++];

            if (result != expected) {
                passed = false;
                errorMsg = "Expected '" + expected + "', got '" + result + "'";
                break;
            }
        }
    }

    cout << "Test #" << testNum << " (" << testName << "): ";
    if (passed) cout << "\033[32mPassed\033[0m" << endl;
    else {
        cout << "\033[31mFailed\033[0m (" << errorMsg << ")" << endl;
        failedTests++;
    }
}

int mainTest() {
    srand(time(0));
    int failedTests = 0, totalTests = 0;

    cout << "=== STANDARD CASES ===" << endl;

    // Test 1: The Example from the Image
    // Logic trace:
    // login(john) -> [john]
    // login(jeff) -> [john, jeff]
    // login(jeff) -> [john] (jeff removed)
    // get -> john
    // login(chriss) -> [john, chriss]
    // login(john) -> [chriss] (john removed)
    // login(adam) -> [chriss, adam]
    // login(sandy) -> [chriss, adam, sandy]
    // get -> chriss
    vector<string> actions1 = {
            "login:john", "login:jeff", "login:jeff", "get",
            "login:chriss", "login:john", "login:adam", "login:sandy", "get"
    };
    vector<string> expected1 = {"john", "chriss"};
    runManualTestCase(++totalTests, "Image Example", actions1, expected1, failedTests);

    // Test 2: All Duplicates
    // A, A, B, B -> returns ""
    vector<string> actions2 = {"login:A", "login:A", "login:B", "login:B", "get"};
    vector<string> expected2 = {""};
    runManualTestCase(++totalTests, "All Duplicates", actions2, expected2, failedTests);

    // Test 3: Simple Sequence
    // A, B, C -> get A -> login A -> get B
    vector<string> actions3 = {"login:A", "login:B", "login:C", "get", "login:A", "get"};
    vector<string> expected3 = {"A", "B"};
    runManualTestCase(++totalTests, "Simple FIFO", actions3, expected3, failedTests);


    cout << endl << "=== STRESS TESTS ===" << endl;

    int stressOps = 20000; // Number of operations
    int userPoolSize = 1000; // Pool of unique names
    int stressFailures = 0;

    Solution userSol;
    ReferenceSolution refSol;

    for(int i=0; i<stressOps; i++) {
        // 90% chance to login, 10% chance to query
        if (rand() % 10 < 9) {
            string name = getRandomUser(userPoolSize);
            userSol.newUserLogin(name);
            refSol.newUserLogin(name);
        } else {
            string userRes = userSol.getOldestOneTimeVisitingUser();
            string refRes = refSol.getOldestOneTimeVisitingUser();

            if (userRes != refRes) {
                stressFailures++;
                failedTests++;
                // Stop on first failure to avoid spamming console
                cout << "\n\033[31mStress Test Failed!\033[0m at op #" << i << endl;
                cout << "Expected: '" << refRes << "', Got: '" << userRes << "'" << endl;
                break;
            }
        }

        if (i % 100 == 0) printProgressBar(i, stressOps);
    }
    printProgressBar(stressOps, stressOps);
    cout << endl;

    // ==========================================
    //  RESULTS
    // ==========================================
    int manualTests = 3;
    // Note: Stress test counts as 1 big test pass/fail in this summary
    bool stressPassed = (stressFailures == 0);
    totalTests = manualTests + 1;
    int finalFailures = failedTests > 0 ? failedTests : (stressPassed ? 0 : 1);

    double successRate = (totalTests - (failedTests > 0 ? 1 : 0)) / (double)totalTests; // Rough calc

    cout << endl << "==========================================" << endl;
    if (failedTests == 0) {
        cout << "\033[32mAll Tests Passed (100%)\033[0m" << endl;
    } else {
        cout << "\033[31mSome Tests Failed\033[0m" << endl;
    }
    cout << "==========================================" << endl;

    return 0;
}