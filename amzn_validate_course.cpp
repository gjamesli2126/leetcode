#include<bits/stdc++.h>
#include <chrono>
#include <thread>
#define mainTest main
using namespace std;

// ==========================================
//  USER SOLUTION CLASS
// ==========================================
class Solution {
public:
    /*
     * Validates the course structure.
     * Returns true if valid (no cycles), false otherwise.
     * c4: <c1,c2,c3>...
     * c6: <c3,c6>
     * c5: <>
     */

    bool validate(unordered_map<string, vector<string>>& db) {
        // TODO: Write your cycle detection logic here
        //db: to<---from_1,from_2,from_3
        unordered_map<string,int> indgree;
        unordered_map<string,vector<string>> from_toS;
        for(const auto& [course,preq]:db){
            for(const string& preq_course:preq) from_toS[preq_course].emplace_back(course);
            indgree[course]=preq.size();
        }
        queue<string> q;
        for(const auto& [course,preq_count]:indgree) if(!preq_count) q.emplace(course);
        int count_steps=0;
        while(!q.empty()){
            string course=q.front();
            q.pop();// <--- 【關鍵點】：這裡代表這門課正式「修過/完成」了！
            ++count_steps;
            for(const string& next_course:from_toS[course]){
                --indgree[next_course];
                if(!indgree[next_course]) q.emplace(next_course);
            }
        }
        return count_steps==db.size();
    }
};

// ==========================================
//  INTERNAL TEST HELPERS (Hidden Logic)
// ==========================================

// A correct reference implementation to verify Random/Stress tests
bool referenceValidate(unordered_map<string, vector<string>>& db) {
    unordered_map<string, int> state; // 0=unvisited, 1=visiting, 2=visited

    function<bool(const string&)> hasCycle = [&](const string& u) -> bool {
        state[u] = 1; // Mark visiting
        if (db.count(u)) {
            for (const string& v : db[u]) {
                if (state[v] == 1) return true; // Cycle detected
                if (state[v] == 0) {
                    if (hasCycle(v)) return true;
                }
            }
        }
        state[u] = 2; // Mark visited
        return false;
    };

    for (auto const& [node, neighbors] : db) {
        if (state[node] == 0) {
            if (hasCycle(node)) return false; // Invalid
        }
    }
    return true; // Valid
}

// Generate a random string node name
string getNodeName(int i) {
    return "Course_" + to_string(i);
}

// Generates a graph. if forceDAG is true, it guarantees no cycles.
unordered_map<string, vector<string>> generateGraph(int nodes, int edges, bool forceDAG) {
    unordered_map<string, vector<string>> db;
    // Initialize nodes
    for(int i=0; i<nodes; i++) db[getNodeName(i)] = {};

    int edgesAdded = 0;
    int attempts = 0;
    while(edgesAdded < edges && attempts < edges * 5) {
        attempts++;
        int u = rand() % nodes;
        int v = rand() % nodes;

        if (u == v) continue; // Avoid self loops in generation unless intended

        // If we want a guaranteed DAG, only allow edges from low index to high index
        if (forceDAG && u > v) swap(u, v);

        // Check if edge already exists
        bool exists = false;
        for(const string& neighbor : db[getNodeName(u)]) {
            if(neighbor == getNodeName(v)) exists = true;
        }

        if(!exists) {
            db[getNodeName(u)].push_back(getNodeName(v));
            edgesAdded++;
        }
    }
    return db;
}

void printProgressBar(int current, int total) {
    int barWidth = 50;
    float progress = (float)current / total;

    cout << "\r[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "=";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %";
    cout.flush();
}

void runTest(int testNum, string testName, unordered_map<string, vector<string>> db, bool expected, int& failedTests) {
    Solution sol;
    bool actual = sol.validate(db);

    cout << "Test #" << testNum << " (" << testName << "): ";
    if (actual == expected) {
        cout << "\033[32m" << "Passed" << "\033[0m";
    } else {
        cout << "\033[31m" << "Failed" << "\033[0m";
        cout << " (Expected: " << (expected ? "Valid" : "Invalid")
             << ", Got: " << (actual ? "Valid" : "Invalid") << ")";
        failedTests++;
    }
    cout << endl;
}

// ==========================================
//  MAIN TEST DRIVER
// ==========================================
int mainTest() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== STANDARD CASES ===" << endl;

    // Test 1: Amazon Example (Valid)
    unordered_map<string, vector<string>> t1;
    t1["Databases"] = {"Security", "Logging"};
    t1["Security"] = {"Logging"};
    t1["Logging"] = {};
    runTest(++totalTests, "Amazon Example", t1, true, failedTests);

    // Test 2: Diamond Graph (Valid)
    // A->B, A->C, B->D, C->D
    unordered_map<string, vector<string>> t2;
    t2["A"] = {"B", "C"};
    t2["B"] = {"D"};
    t2["C"] = {"D"};
    t2["D"] = {};
    runTest(++totalTests, "Diamond DAG", t2, true, failedTests);

    // Test 3: Simple Cycle (Invalid)
    unordered_map<string, vector<string>> t3;
    t3["A"] = {"B"};
    t3["B"] = {"A"};
    runTest(++totalTests, "Simple Cycle", t3, false, failedTests);

    // Test 4: Disconnected with Cycle (Invalid)
    // A->B (ok), C->C (bad)
    unordered_map<string, vector<string>> t4;
    t4["A"] = {"B"};
    t4["B"] = {};
    t4["C"] = {"C"};
    runTest(++totalTests, "Disconnected + Self Loop", t4, false, failedTests);

    // Test 5: Empty Graph (Valid)
    unordered_map<string, vector<string>> t5;
    runTest(++totalTests, "Empty Graph", t5, true, failedTests);

    // Test 6: Linear Chain (Valid)
    // 0->1->2->3...->99
    unordered_map<string, vector<string>> t6;
    for(int i=0; i<99; i++) t6[to_string(i)] = {to_string(i+1)};
    t6["99"] = {};
    runTest(++totalTests, "Long Chain", t6, true, failedTests);

    cout << endl << "=== STRESS TESTS ===" << endl;

    int stressCount = 100;
    int stressFailures = 0;

    for(int i=0; i<stressCount; i++) {
        // Randomly decide if we force a DAG or allow random edges (likely cycles)
        bool forceDAG = (rand() % 2 == 0);
        int nodes = 50 + (rand() % 50); // 50 to 100 nodes
        int edges = nodes + (rand() % nodes); // Sparse-ish graph

        auto db = generateGraph(nodes, edges, forceDAG);

        // Calculate Ground Truth
        bool expected = referenceValidate(db);

        // Run User Solution
        Solution sol;
        bool actual = sol.validate(db);

        if (actual != expected) {
            stressFailures++;
            failedTests++; // Add to global fail count
        }

        printProgressBar(i + 1, stressCount);
        // Small sleep to make the bar visible (optional, remove for speed)
        // this_thread::sleep_for(chrono::milliseconds(5));
    }
    cout << endl; // New line after progress bar

    // ==========================================
    //  RESULTS
    // ==========================================
    totalTests += stressCount; // Add stress tests to total
    double errorRate = static_cast<double>(failedTests) / totalTests;
    double successRate = 1.0 - errorRate;

    cout << endl << "==========================================" << endl;
    cout << "Final Report" << endl;
    cout << "Standard Tests: " << (totalTests - stressCount - (failedTests - stressFailures))
         << "/" << (totalTests - stressCount) << " Passed" << endl;
    cout << "Stress Tests:   " << (stressCount - stressFailures) << "/" << stressCount << " Passed" << endl;

    cout << "Success Rate: ";
    if (successRate == 1.0) {
        cout << "\033[32m" << "100.0%" << "\033[0m"; // Green
    } else if (successRate > 0.8) {
        cout << "\033[33m" << successRate * 100.0 << "%" << "\033[0m"; // Yellow
    } else {
        cout << "\033[31m" << successRate * 100.0 << "%" << "\033[0m"; // Red
    }
    cout << endl << "==========================================" << endl;

    return 0;
}