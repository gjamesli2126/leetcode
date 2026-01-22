#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// ==========================================
// 1. Solution 風格的 PackageManager
// ==========================================
class PackageManager {
public:
    // Twist Requirement: 存儲傳遞依賴 (Ancestors)
    // Key: Package, Value: Set of all dependencies (direct & transitive)
    unordered_map<string, unordered_set<string>> ancestors;

    // Input: dependencies where {A, B} means "A depends on B"
    vector<string> installPackages(vector<pair<string, string>>& dependencies) {
        // create from->to table (Dependency -> Package)
        unordered_map<string, vector<string>> from_toS;
        // create lock(indegree) table
        unordered_map<string, int> to_indgree;

        unordered_set<string> all_nodes;

        // 1. Build Graph
        for(const auto& dep_pair : dependencies){
            string from = dep_pair.second; // Dependency (先裝)
            string to = dep_pair.first;    // Package (後裝)

            from_toS[from].emplace_back(to);
            ++to_indgree[to];

            all_nodes.insert(from);
            all_nodes.insert(to);
        }

        // 2. Initialize Queue with 0-indegree nodes
        queue<string> q;
        for(const auto& node : all_nodes) {
            // 如果不在 map 中或者值為 0，代表沒有依賴
            if(!to_indgree[node]) q.emplace(node);
        }

        vector<string> order;
        ancestors.clear();

        // 3. Process (BFS / Kahn's Algorithm)
        while(!q.empty()){
            string course = q.front();
            q.pop();
            order.emplace_back(course);

            if(from_toS.contains(course)){
                for(const string& to : from_toS[course]){
                    // Twist Logic: "to" 繼承 "course" 的所有依賴
                    ancestors[to].insert(course);
                    ancestors[to].insert(ancestors[course].begin(), ancestors[course].end());

                    --to_indgree[to];
                    if(!to_indgree[to]) q.emplace(to); // meaning the package can be installed
                }
            }
        }

        // Check for cycles
        if(all_nodes.size() == order.size()) return order;
        return {}; // Return empty if cycle detected
    }
};

// ==========================================
// 2. 測試輔助工具 (Colors, Validators)
// ==========================================

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// 驗證拓撲排序的合法性
// 規則：對於依賴對 {A, B} (A depends on B)，B 必須在 A 之前出現
bool verifyOrder(const vector<string>& order, const vector<pair<string, string>>& deps) {
    if (order.empty()) return false;

    unordered_map<string, int> pos;
    for (int i = 0; i < order.size(); i++) {
        pos[order[i]] = i;
    }

    for (auto& p : deps) {
        string pkg = p.first;
        string dep = p.second;

        // 如果任一包沒在結果中，或者順序錯誤 (Dep 在 Pkg 之後)
        if (pos.find(pkg) == pos.end() || pos.find(dep) == pos.end()) return false;
        if (pos[dep] > pos[pkg]) return false;
    }
    return true;
}

void runTest(int testId, string testName,
             vector<pair<string, string>> deps,
             bool expectSuccess,
             int& failedTests) {

    PackageManager pm;
    vector<string> result = pm.installPackages(deps);
    bool actualSuccess = !result.empty();

    // 如果預期失敗(Cycle)，actualSuccess 為 false 即正確
    // 如果預期成功，actualSuccess 需為 true 且順序必須合法
    bool pass = false;
    if (!expectSuccess) {
        pass = !actualSuccess;
    } else {
        pass = actualSuccess && verifyOrder(result, deps);
    }

    cout << "Test " << testId << " [" << testName << "]: ";
    if (pass) {
        cout << GREEN << "PASS" << RESET << endl;
    } else {
        failedTests++;
        cout << RED << "FAIL" << RESET << endl;
        cout << "   Expected Success: " << expectSuccess << ", Got Result Size: " << result.size() << endl;
    }
}

// ==========================================
// 3. 隨機數據生成器 (Stress Tests)
// ==========================================

struct StressCase {
    vector<pair<string, string>> deps;
    bool shouldSucceed;
};

// 生成 DAG (預期成功)
StressCase generateDAG(int numNodes, int numEdges) {
    StressCase sc;
    sc.shouldSucceed = true;
    vector<string> nodes;
    for(int i=0; i<numNodes; i++) nodes.push_back("P" + to_string(i));

    for(int i=0; i<numEdges; i++) {
        int u = rand() % numNodes;
        int v = rand() % numNodes;
        if (u == v) continue;
        // 強制小 index 依賴大 index (或反之) 以保證無環
        if (u < v) sc.deps.push_back({nodes[u], nodes[v]});
        else sc.deps.push_back({nodes[v], nodes[u]});
    }
    return sc;
}

// 生成 Cycle (預期失敗)
StressCase generateCycle(int numNodes) {
    StressCase sc;
    sc.shouldSucceed = false;
    vector<string> nodes;
    for(int i=0; i<numNodes; i++) nodes.push_back("P" + to_string(i));

    // 構建環 P0 -> P1 -> ... -> Pk -> P0
    for(int i=0; i<numNodes; i++) {
        string u = nodes[i];
        string v = nodes[(i + 1) % numNodes];
        sc.deps.push_back({u, v}); // u depends on v
    }
    return sc;
}

// ==========================================
// 4. Main Function
// ==========================================
int main() {
    srand(time(0));
    int failedTests = 0;
    int totalTests = 0;

    cout << "=== Manual Corner Cases ===" << endl;

    // Test 1: Simple Chain
    {
        // A depends on B, B depends on C
        vector<pair<string, string>> deps = {{"A", "B"}, {"B", "C"}};
        runTest(++totalTests, "Chain A->B->C", deps, true, failedTests);
    }

    // Test 2: Diamond Shape
    {
        // A depends on B, C; B->D, C->D
        vector<pair<string, string>> deps = {
                {"A", "B"}, {"A", "C"},
                {"B", "D"}, {"C", "D"}
        };
        runTest(++totalTests, "Diamond Graph", deps, true, failedTests);
    }

    // Test 3: Simple Cycle
    {
        // A depends on B, B depends on A
        vector<pair<string, string>> deps = {{"A", "B"}, {"B", "A"}};
        runTest(++totalTests, "Simple Cycle", deps, false, failedTests);
    }

    // Test 4: Disconnected Components
    {
        // A->B and C->D
        vector<pair<string, string>> deps = {{"A", "B"}, {"C", "D"}};
        runTest(++totalTests, "Disconnected Graph", deps, true, failedTests);
    }

    // Test 5: Complex Twist Check (Verify Ancestors Manually)
    {
        cout << "Test " << ++totalTests << " [Twist: Transitive Check]: ";
        PackageManager pm;
        // A->B->C
        vector<pair<string, string>> deps = {{"A", "B"}, {"B", "C"}};
        pm.installPackages(deps);

        // Check if A transitively depends on C
        if (pm.ancestors["A"].count("C")) {
            cout << GREEN << "PASS" << RESET << endl;
        } else {
            failedTests++;
            cout << RED << "FAIL (Transitive dependency missing)" << RESET << endl;
        }
    }

    cout << "\n=== Randomized Stress Tests ===" << endl;

    for (int i = 0; i < 20; i++) {
        // Case 1: Valid DAGs
        StressCase dag = generateDAG(10 + rand()%20, 15 + rand()%20);
        runTest(++totalTests, "Random DAG", dag.deps, dag.shouldSucceed, failedTests);

        // Case 2: Cyclic Graphs
        StressCase cycle = generateCycle(5 + rand()%5);
        runTest(++totalTests, "Random Cycle", cycle.deps, cycle.shouldSucceed, failedTests);
    }

    // ==========================================
    // Report
    // ==========================================
    double errorRate = (totalTests == 0) ? 0.0 : static_cast<double>(failedTests) / totalTests;
    cout << "\n------------------------------------------------" << endl;
    cout << "Total Tests: " << totalTests << endl;
    cout << "Error Rate: ";
    if (errorRate == 0) {
        cout << "\033[94m" << "0%" << RESET;
    } else {
        cout << "\033[33m" << errorRate * 100 << "%" << RESET;
    }
    cout << endl;

    return 0;
}