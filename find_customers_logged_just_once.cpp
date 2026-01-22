#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <ctime>

// Macro to avoid main function conflict
#define mainTest main

using namespace std;

// ==========================================
// YOUR OPTIMIZED SOLUTION (O(1))
// ==========================================
class LoginTracker {
private:
    unordered_map<string,list<string>::iterator> one_time_set;
    unordered_set<string> n_time_set;
    list<string> lru;

public:
    void newUserLogin(const string& username) {
        if(n_time_set.contains(username)) return;
        if(one_time_set.contains(username)){
            n_time_set.emplace(username);
            lru.erase(one_time_set[username]);
            one_time_set.erase(username);
            return;
        }
        lru.emplace_back(username);
        one_time_set.emplace(username,prev(lru.end()));
    }

    string getOldestOneTimeVisitingUser() {
        if(lru.empty()) return "";
        return *lru.begin();
    }
};

// ==========================================
// TEST HARNESS UTILITIES
// ==========================================

// Trusted Reference Oracle (Brute Force)
// Time Complexity: O(N) per query (slow but correct)
class BruteForceTracker {
    vector<string> arrivalOrder;
    unordered_map<string, int> counts;
public:
    void newUserLogin(string username) {
        if (counts.find(username) == counts.end()) {
            arrivalOrder.push_back(username);
        }
        counts[username]++;
    }

    string getOldestOneTimeVisitingUser() {
        // Iterate through arrival history to find the first one with count == 1
        for (const string& user : arrivalOrder) {
            if (counts[user] == 1) return user;
        }
        return "";
    }
};

// Helper: Run a single sequence test
void runManualTest(int testId, const vector<string>& actions, const vector<string>& params, const vector<string>& expected) {
    LoginTracker sol;
    cout << "Test #" << testId << ": ";

    bool passed = true;
    int checkIdx = 0;

    for (size_t i = 0; i < actions.size(); ++i) {
        if (actions[i] == "login") {
            sol.newUserLogin(params[i]);
        } else if (actions[i] == "get") {
            string actual = sol.getOldestOneTimeVisitingUser();
            string expect = expected[checkIdx++];
            if (actual != expect) {
                cout << "\033[31m" << "Failed" << "\033[0m";
                cout << " | Step " << i << " (get) -> Expected: '" << expect << "', Actual: '" << actual << "'";
                passed = false;
                break;
            }
        }
    }

    if (passed) cout << "\033[32m" << "Passed" << "\033[0m";
    cout << endl;
}

// Helper: Randomized Stress Test
void runStressTest(int numOperations, int userPoolSize, int& failedTests) {
    LoginTracker sol;
    BruteForceTracker ref;

    vector<string> userPool;
    for(int i=0; i<userPoolSize; ++i) userPool.push_back("User" + to_string(i));

    bool failed = false;

    for (int i = 0; i < numOperations; ++i) {
        // 80% chance to login, 20% chance to query
        if (rand() % 5 != 0) {
            string user = userPool[rand() % userPoolSize];
            sol.newUserLogin(user);
            ref.newUserLogin(user);
        } else {
            string actual = sol.getOldestOneTimeVisitingUser();
            string expected = ref.getOldestOneTimeVisitingUser();

            if (actual != expected) {
                cout << "\033[31m" << "Stress Test Failed" << "\033[0m" << endl;
                cout << "  Operation #" << i << endl;
                cout << "  Expected: " << (expected.empty() ? "(empty)" : expected) << endl;
                cout << "  Actual:   " << (actual.empty() ? "(empty)" : actual) << endl;
                failed = true;
                failedTests++;
                break;
            }
        }
    }
    if (!failed) {
        // cout << "Stress test passed." << endl; // Optional: too noisy for loop
    }
}

int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Manual Edge Cases ===" << endl;

    // Test 1: Basic functionality
    // login A -> get(A) -> login B -> get(A) -> login A -> get(B)
    {
        vector<string> acts = {"login", "get", "login", "get", "login", "get"};
        vector<string> pars = {"A", "", "B", "", "A", ""};
        vector<string> exps = {"A", "A", "B"};
        runManualTest(++totalTests, acts, pars, exps);
    }

    // Test 2: All duplicates
    // login A, login A, get -> ""
    {
        vector<string> acts = {"login", "login", "get"};
        vector<string> pars = {"A", "A", ""};
        vector<string> exps = {""};
        runManualTest(++totalTests, acts, pars, exps);
    }

    // Test 3: Complex removal order
    // login A, login B, login C -> get(A)
    // login A -> get(B)
    // login B -> get(C)
    // login C -> get("")
    {
        vector<string> acts = {"login", "login", "login", "get", "login", "get", "login", "get", "login", "get"};
        vector<string> pars = {"A", "B", "C", "", "A", "", "B", "", "C", ""};
        vector<string> exps = {"A", "B", "C", ""};
        runManualTest(++totalTests, acts, pars, exps);
    }

    // Test 4: Resurrection Attempt (Should fail)
    // login A -> login A -> login A -> get("")
    // A should not come back even if logged in 3rd time
    {
        vector<string> acts = {"login", "login", "login", "get"};
        vector<string> pars = {"A", "A", "A", ""};
        vector<string> exps = {""};
        runManualTest(++totalTests, acts, pars, exps);
    }

    cout << "\n=== Running 100 Randomized Stress Tests ===" << endl;

    int stressRounds = 100;
    for (int i = 0; i < stressRounds; ++i) {
        // 1000 operations per test, pool of 50 users
        runStressTest(1000, 50, failedTests);
        totalTests++;
    }

    // ==========================================
    // ERROR RATE REPORT
    // ==========================================
    double errorRate = static_cast<double>(failedTests) / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << "\033[0m";
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << "\033[0m";
    }
    cout << endl;

    return 0;
}