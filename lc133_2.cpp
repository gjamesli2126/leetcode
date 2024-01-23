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
    unordered_map<int,Node*> val2node;
    unordered_map<Node*,vector<int>> node2nei;
    void dfsScout(Node *node){
        if(val2node.contains(node->val)) return;
        Node* newNode=new Node(node->val);
        val2node[node->val]=newNode;
        for(const auto& nei:node->neighbors){
            node2nei[newNode].push_back(nei->val);
            dfsScout(nei);
        }
    }
    void dfsBuild(Node *root){
        if(!root->neighbors.empty()) return;//meaning visited
        //build each node's neighbors
        for(const int& nei:node2nei[root]){
            root->neighbors.push_back(val2node[nei]);
            dfsBuild(val2node[nei]);
        }
    }
public:
    Node* cloneGraph(Node* node) {
        if(node== nullptr) return nullptr;
        Node *root=node;
        //traverse to build graph
        dfsScout(node);
        //traverse graph to build
        dfsBuild(val2node[root->val]);
        return val2node[root->val];
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
