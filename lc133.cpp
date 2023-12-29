#include<bits/stdc++.h>
using namespace std;
// Definition for a Node.
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
public:
    unordered_map<int,vector<int>> dict;
    unordered_map<int,Node*> val2node;
    void bfsGetMap(Node* node){
        deque<Node*> q{node};
        dict[node->val]=vector<int>{};
        while(!q.empty()){
            Node* n=q.front();
            q.pop_front();
            for(Node*& nei:n->neighbors){// may have issue here '&', howabout adding const?
                if(dict.find(nei->val)==dict.end()){
                    dict[nei->val]=vector<int>{};
                    q.push_back(nei);//q 只允許 input vector NOT const vec
                } 
                dict[n->val].push_back(nei->val);
            }
        }
    }
    void createGraph(Node*& node){
        for(const auto& [val,_]:dict){
            val2node[val]=new Node(val);
        }
        for(const auto& [n,vec]:dict){
            //for each n
            for(const int nei:vec){
                val2node[n]->neighbors.push_back(val2node[nei]);
            }
        }
        node=val2node[1];
    }

    Node* cloneGraph(Node* node) {
        if(node==nullptr) return nullptr;
       //用bfs建立 hashmap for neighbers
        bfsGetMap(node);
        Node* node2;
        createGraph(node2);
        return node2;
    }
};