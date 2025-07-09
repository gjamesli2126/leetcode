#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors(vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(vector<Node*>()) {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};
*/

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors(vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(vector<Node*>()) {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;
        unordered_map<Node*,Node*> old_new;
        old_new[node]=new Node(node->val);

        queue<Node*> q;
        q.push(node);
//        unordered_set<Node*> visited_old;
        //one pass
        while(!q.empty()){
            Node* oldNode=q.front();
            q.pop();
            Node* newNode=old_new[oldNode];

            for(Node* oldNei:oldNode->neighbors){
                Node* newNei;
                if(old_new.contains(oldNei)) newNei=old_new[oldNei];
                else {
                    newNei=new Node(oldNei->val);
                    old_new[oldNei]=newNei;
                    q.push(oldNei);//use if found in the hashmap to 代替 visited_old
                }
                newNode->neighbors.push_back(newNei);
            }
        }
        return old_new[node];
    }
};
// Helper function: Build a graph from an adjacency list representation.
// Each index i in the input vector corresponds to the node with value i+1.
// For example, if adjList = [[2,4],[1,3],[2,4],[1,3]],
// then node 1's neighbors are nodes with values 2 and 4, etc.
Node* buildGraph(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    if(n == 0) return nullptr;
    // Create nodes indexed from 1 to n (1-indexed values)
    vector<Node*> nodes(n + 1, nullptr);
    for (int i = 1; i <= n; i++) {
        nodes[i] = new Node(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int neigh : adjList[i - 1]) {
            // Add neighbor (which is a node with value 'neigh')
            nodes[i]->neighbors.push_back(nodes[neigh]);
        }
    }
    // Return the node with value 1 as the starting node.
    return nodes[1];
}

// Helper function: Convert a graph to its adjacency list representation.
// Traverses the graph using BFS starting from 'node'.
// Returns a vector where the i-th element (0-indexed) corresponds to the
// sorted list of neighbors of the node with value i+1.
vector<vector<int>> getGraphAdjList(Node* node) {
    vector<vector<int>> res;
    if(!node) return res;
    unordered_map<int, vector<int>> mp;
    unordered_set<int> visited;
    queue<Node*> q;
    q.push(node);
    visited.insert(node->val);
    while(!q.empty()){
        Node* cur = q.front(); q.pop();
        for(Node* nb : cur->neighbors) {
            mp[cur->val].push_back(nb->val);
            if(visited.find(nb->val) == visited.end()){
                visited.insert(nb->val);
                q.push(nb);
            }
        }
    }
    // Since the graph is connected and nodes are labeled from 1 to n,
    // determine n as the size of visited set.
    int n = visited.size();
    res.resize(n);
    // For each node value from 1 to n, assign its neighbor list (or empty vector)
    for (int i = 1; i <= n; i++){
        if(mp.find(i) != mp.end()){
            res[i - 1] = mp[i];
            sort(res[i - 1].begin(), res[i - 1].end());
        } else {
            res[i - 1] = {};
        }
    }
    return res;
}

// Helper function to free the graph nodes (using BFS).
void freeGraph(Node* node) {
    if(!node) return;
    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(node);
    visited.insert(node);
    while(!q.empty()){
        Node* cur = q.front(); q.pop();
        for(Node* nb : cur->neighbors){
            if(visited.find(nb) == visited.end()){
                visited.insert(nb);
                q.push(nb);
            }
        }
        delete cur;
    }
}

// Helper function to run a test case and print pass (green) or fail (red).
void runTest(int testNum, vector<vector<int>> inputAdjList, vector<vector<int>> expectedAdjList) {
    // Build the original graph.
    Node* original = buildGraph(inputAdjList);

    // Instantiate Solution and clone the graph.
    Solution sol;
    Node* cloned = sol.cloneGraph(original);

    // Convert the cloned graph to an adjacency list.
    vector<vector<int>> resultAdjList = getGraphAdjList(cloned);

    // For comparison, sort each neighbor list in expected and result.
    for(auto &neighbors : expectedAdjList) {
        sort(neighbors.begin(), neighbors.end());
    }
    for(auto &neighbors : resultAdjList) {
        sort(neighbors.begin(), neighbors.end());
    }

    bool pass = (resultAdjList == expectedAdjList);
    if(pass) {
        cout << "\033[1;32mTest Case " << testNum
             << " Passed: cloneGraph(adjList) = " << endl;
        for(auto &vec : resultAdjList){
            cout << "[";
            for (int i = 0; i < vec.size(); i++){
                cout << vec[i] << (i < vec.size()-1 ? ", " : "");
            }
            cout << "] ";
        }
        cout << "\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum
             << " Failed: cloneGraph(adjList) = " << endl;
        cout << "Got: " << endl;
        for(auto &vec : resultAdjList){
            cout << "[";
            for (int i = 0; i < vec.size(); i++){
                cout << vec[i] << (i < vec.size()-1 ? ", " : "");
            }
            cout << "] ";
        }
        cout << endl << "Expected: " << endl;
        for(auto &vec : expectedAdjList){
            cout << "[";
            for (int i = 0; i < vec.size(); i++){
                cout << vec[i] << (i < vec.size()-1 ? ", " : "");
            }
            cout << "] ";
        }
        cout << "\033[0m" << endl;
    }

    // Free both graphs.
    freeGraph(original);
    freeGraph(cloned);
}

int testMain(){
    // Test Case 1:
    // Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
    // Expected Output: [[2,4],[1,3],[2,4],[1,3]]
    runTest(1, {{2,4}, {1,3}, {2,4}, {1,3}}, {{2,4}, {1,3}, {2,4}, {1,3}});

    // Test Case 2:
    // Input: adjList = [[]]
    // Expected Output: [[]]
    runTest(2, {{}}, {{}});

    // Test Case 3:
    // Input: adjList = []
    // Expected Output: [] (empty graph)
    runTest(3, {}, {});

    return 0;
}