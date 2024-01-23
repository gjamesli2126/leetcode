#include <bits/stdc++.h>
using namespace std;
#define mainTest main
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
private:
    unordered_map<Node*,Node*> old2newmap;
    Node* dfsScoutandBuild(Node *node){
        if(old2newmap.contains(node)) return old2newmap[node];
        Node *newNode=new Node(node->val);
        old2newmap[node]=newNode;
        for(Node*const& nei:node->neighbors){
            newNode->neighbors.push_back(dfsScoutandBuild(nei));
        }
        return newNode;
    }
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        return dfsScoutandBuild(node);
    }
};

// Helper function to build a graph from an adjacency list
Node* buildGraph(const vector<vector<int>>& adjList) {
    if (adjList.empty()) return nullptr;

    vector<Node*> nodes(adjList.size(), nullptr);
    for (int i = 0; i < adjList.size(); ++i) {
        if (!nodes[i]) {
            nodes[i] = new Node(i + 1);
        }
        for (int j : adjList[i]) {
            if (!nodes[j - 1]) {
                nodes[j - 1] = new Node(j);
            }
            nodes[i]->neighbors.push_back(nodes[j - 1]);
        }
    }
    return nodes[0];
}

// Helper function to compare two graphs
bool compareGraphs(Node* node1, Node* node2, unordered_set<Node*>& visited) {
    if (!node1 && !node2) return true;
    if ((!node1 && node2) || (node1 && !node2)) return false;
    if (node1->val != node2->val) return false;
    if (visited.find(node1) != visited.end()) return true;

    visited.insert(node1);
    if (node1->neighbors.size() != node2->neighbors.size()) return false;

    for (int i = 0; i < node1->neighbors.size(); ++i) {
        if (!compareGraphs(node1->neighbors[i], node2->neighbors[i], visited)) {
            return false;
        }
    }
    return true;
}

int mainTest() {
    vector<vector<vector<int>>> testCases = {
            {{2, 4}, {1, 3}, {2, 4}, {1, 3}},
            {{}},
            {}
            // Add more test cases here
    };

    int totalTests = static_cast<int>(testCases.size());
    int passedTests = 0;

    for (int i = 0; i < totalTests; ++i) {
        Solution sol;
        Node* originalGraph = buildGraph(testCases[i]);
        Node* clonedGraph = sol.cloneGraph(originalGraph);

        unordered_set<Node*> visited;
        bool passed = compareGraphs(originalGraph, clonedGraph, visited);

        // Print test case details
        cout << "Test Case " << (i + 1) << ":" << endl;
        cout << "Expected: Clone of the original graph" << endl;
        cout << "Result: " << (passed ? "Pass" : "Fail") << endl;

        // Check and print test result
        if (passed) {
            cout << "\033[32mPass\033[0m" << endl; // Green color for pass
            ++passedTests;
        } else {
            cout << "\033[31mFail\033[0m" << endl; // Red color for fail
        }
        cout << endl;
    }

    // Print summary
    cout << "Passed " << passedTests << " out of " << totalTests << " tests." << endl;
    if (passedTests < totalTests) {
        cout << "\033[31mError Rate: " << (totalTests - passedTests) << "/" << totalTests << "\033[0m" << endl; // Red color for error rate if > 0
    } else {
        cout << "\033[32mError Rate: " << (totalTests - passedTests) << "/" << totalTests << "\033[0m" << endl; // Green color for error rate if 0
    }

    return 0;
}
