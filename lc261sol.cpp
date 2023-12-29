#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<int> nodes(n, 0); // nodes = [0, 1, 2, 3, 4]
        for (int i = 0; i < n; i++) nodes[i] = i; // nodes = [0, 1, 2, 3, 4]
        // Iterate over each edge
        for (int i = 0; i < edges.size(); i++) {
            int f = edges[i].first; // f is the first node of the i-th edge
            int s = edges[i].second; // s is the second node of the i-th edge
            // Find the root of the first node of the edge
            while (nodes[f] != f){
                cout<<"trace(f): "<<nodes[f]<<" = nodes["<<f<<"]"<<endl;
                f = nodes[f]; // f becomes the root of the first node
            } 
            cout<<"Final(f): "<<nodes[f]<<" = nodes["<<f<<"]"<<endl;
            // For each edge, f will eventually become 0, 1, 2, or 3
            // Find the root of the second node of the edge
            while (nodes[s] != s){
                cout<<"trace(s): "<<nodes[s]<<" = nodes["<<s<<"]"<<endl;
                 s = nodes[s]; // s becomes the root of the second node
            }
            cout<<"Final(s): "<<nodes[s]<<" = nodes["<<s<<"]"<<endl;
            // For each edge, s will eventually become 0, 1, 2, or 3
            // If both nodes have the same root, a cycle is found
            if (nodes[f] == nodes[s]) return false; // Returns false if a cycle is detected
            // This will be true for the edge [1,3], where both 1 and 3 have the same root
            // Union: set the root of the second node to be the first node
            nodes[s] = f; // The root of the second node is set to be the first node
        }

        // Check if the number of edges is exactly one less than the number of nodes
        return edges.size() == n - 1; // Returns true if edges.size() == 4
        // This will return false since edges.size() is 5, not 4
    }
};

// Given the input, the function will return false, indicating the graph is not a valid tree.
