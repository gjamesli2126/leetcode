#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define mainTest main
using namespace std;

// ==========================================
//  USER DEFINED STRUCTURES
// ==========================================
// The prompt asks to "Define what a package looks like"
// (Though for this algorithm, we mostly use the map, this struct demonstrates design intent)
struct Package {
    string name;
    vector<string> dependencies;

    Package(string n) : name(n) {}
};

// ==========================================
//  USER SOLUTION
// ==========================================
class Solution {
private:
    unordered_set<string> visited,visiting;
    vector<string> order;
public:
    /*
     * Task: Given a target package and a repository of all packages,
     * return a valid installation order.
     * * Rules:
     * 1. A package must be installed AFTER its dependencies.
     * 2. You only need to install the target and its transitive dependencies.
     * * @param targetPackage: The name of the package we want to install.
     * @param repo: A map where Key = Package Name, Value = List of Dependency Names.
     * @return: A vector of strings representing the installation order.
     */
    void dfs(const string& pkg,unordered_map<string,vector<string>>& repo){
        if(visited.contains(pkg)) return;
        if(visiting.contains(pkg)) throw "loop :)";
        visiting.insert(pkg);
        for(const string& dep:repo[pkg]) dfs(dep,repo);
        visiting.erase(pkg);
        visited.insert(pkg);
        order.emplace_back(pkg);
    }
    vector<string> install(string targetPackage, unordered_map<string, vector<string>>& repo) {
        dfs(targetPackage,repo);
        return order;
    }
};

// ==========================================
//  TESTING INFRASTRUCTURE (VALIDATORS)
// ==========================================

// Helper: Verifies that the install order is valid for the given dependency graph
bool validateOrder(const string& target, unordered_map<string, vector<string>>& repo, const vector<string>& result) {
    if (result.empty()) return false; // Assuming valid graph, should not be empty

    // Check 1: Is the target actually in the list? (It usually should be last)
    bool targetFound = false;
    for(const string& s : result) if(s == target) targetFound = true;
    if(!targetFound) return false;

    unordered_set<string> installed;
    unordered_set<string> resultSet(result.begin(), result.end());

    // Check 2: Order Constraints
    for (const string& pkg : result) {
        // If this package has dependencies, they must have been installed ALREADY
        if (repo.count(pkg)) {
            for (const string& dep : repo[pkg]) {
                // crucial: We only care about dependencies that are actually PART of this installation tree.
                // If a dependency is missing from the result entirely, that's a different check (completeness).
                // But if it IS in the result, it MUST come before 'pkg'.
                if (resultSet.count(dep)) {
                    if (installed.find(dep) == installed.end()) {
                        // Error: 'dep' is needed for 'pkg' but hasn't been installed yet
                        return false;
                    }
                }
            }
        }
        installed.insert(pkg);
    }

    // Check 3: Completeness (Did we install everything required by the target?)
    // This is a simple recursive check to ensure no transitive dependency was skipped.
    vector<string> stack;
    stack.push_back(target);
    unordered_set<string> needed;
    while(!stack.empty()){
        string curr = stack.back(); stack.pop_back();
        if(needed.count(curr)) continue;
        needed.insert(curr);
        if(repo.count(curr)){
            for(const string& dep : repo[curr]) stack.push_back(dep);
        }
    }

    for(const string& need : needed) {
        if(!resultSet.count(need)) return false; // Missing a required dependency
    }

    return true;
}

// Generates a random DAG (Package Repo)
unordered_map<string, vector<string>> generateRepo(int size, int maxDeps) {
    unordered_map<string, vector<string>> repo;
    for(int i=0; i<size; ++i) repo["P" + to_string(i)] = {};

    for(int i=0; i<size; ++i) {
        int numDeps = rand() % maxDeps;
        for(int j=0; j<numDeps; ++j) {
            int depId = rand() % size;
            // Force DAG: Only depend on lower IDs to prevent cycles easily
            if (depId < i) {
                repo["P" + to_string(i)].push_back("P" + to_string(depId));
            }
        }
    }
    return repo;
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

void runTest(int testNum, string testName, string target,
             unordered_map<string, vector<string>> repo, int& failedTests) {
    Solution sol;
    vector<string> actual = sol.install(target, repo);

    bool valid = validateOrder(target, repo, actual);

    cout << "Test #" << testNum << " (" << testName << "): ";
    if (valid) {
        cout << "\033[32mPassed\033[0m";
    } else {
        cout << "\033[31mFailed\033[0m";
        failedTests++;
    }
    cout << endl;
}

int mainTest() {
    srand(time(0));
    int failedTests = 0, totalTests = 0;

    cout << "=== STANDARD CASES ===" << endl;

    // Test 1: Image Example
    // A -> B, C
    // B -> D, E, F
    // C -> F
    unordered_map<string, vector<string>> t1;
    t1["A"] = {"B", "C"};
    t1["B"] = {"D", "E", "F"};
    t1["C"] = {"F"};
    t1["D"] = {}; t1["E"] = {}; t1["F"] = {};
    runTest(++totalTests, "Image Example", "A", t1, failedTests);

    // Test 2: Linear Dependency
    // Install A: A->B->C
    unordered_map<string, vector<string>> t2;
    t2["A"] = {"B"};
    t2["B"] = {"C"};
    t2["C"] = {};
    runTest(++totalTests, "Linear Chain", "A", t2, failedTests);

    // Test 3: Diamond Dependency (Shared dependency)
    // A->B, A->C, B->D, C->D
    unordered_map<string, vector<string>> t3;
    t3["A"] = {"B", "C"};
    t3["B"] = {"D"};
    t3["C"] = {"D"};
    t3["D"] = {};
    runTest(++totalTests, "Diamond Graph", "A", t3, failedTests);

    // Test 4: Single Package (No deps)
    unordered_map<string, vector<string>> t4;
    t4["Z"] = {};
    runTest(++totalTests, "Single Package", "Z", t4, failedTests);

    // Test 5: Unrelated packages (Should not include X or Y)
    // A -> B. (X -> Y exists in repo but irrelevant)
    unordered_map<string, vector<string>> t5;
    t5["A"] = {"B"};
    t5["B"] = {};
    t5["X"] = {"Y"};
    t5["Y"] = {};
    runTest(++totalTests, "Irrelevant Branches", "A", t5, failedTests);

    cout << endl << "=== STRESS TESTS ===" << endl;

    int stressCount = 5000;
    int stressFailures = 0;

    for(int i=0; i<stressCount; ++i) {
        int size = 20 + (rand() % 30); // 20-50 packages
        auto repo = generateRepo(size, 4); // Random DAG
        string target = "P" + to_string(size - 1); // Install the highest ID

        Solution sol;
        vector<string> res = sol.install(target, repo);

        if (!validateOrder(target, repo, res)) {
            stressFailures++;
            failedTests++;
        }

        if (i % 100 == 0) printProgressBar(i, stressCount);
    }
    printProgressBar(stressCount, stressCount);
    cout << endl;

    // ==========================================
    //  RESULTS
    // ==========================================
    totalTests += stressCount; // Adjust count logic
    // Note: We count the stress loop as 'stressCount' individual tests

    double errorRate = (double)failedTests / totalTests;
    double successRate = 1.0 - errorRate;

    cout << endl << "==========================================" << endl;
    cout << "Final Report" << endl;
    if (failedTests == 0) {
        cout << "\033[32mAll Tests Passed (100%)\033[0m" << endl;
    } else {
        cout << "Success Rate: ";
        if (successRate > 0.8) cout << "\033[33m";
        else cout << "\033[31m";
        cout << (successRate * 100.0) << "%\033[0m" << endl;
    }
    cout << "==========================================" << endl;

    return 0;
}