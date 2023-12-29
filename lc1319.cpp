#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    unordered_set<int> visited;
    unordered_map<int,unordered_set<int>> dict;
    void dfs(int node){
        // connect all the dots
        visited.insert(node);
        for(const int& n:dict[node]){
            if(visited.find(n)!=visited.end()) continue;;
            dfs(n);
        }
    }
    void dfsIter(const int& node){
        stack<int> stk;
        stk.push(node);
        while(!stk.empty()){
            int com=stk.top();
            visited.insert(com);
            stk.pop();
            for(const int& com2:dict[com]){
                if(visited.find(com2)!=visited.end()) continue;
                stk.push(com2);
            }
        }
    }
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        //if connection not enought then return -1
        if(n>connections.size()+1) return -1;
        //else onlt calc required additional line as we can assert that the line_num is enough     
        for(const auto& pr:connections){
            dict[pr[0]].insert(pr[1]);
            dict[pr[1]].insert(pr[0]);
        }
        int newConnectedComputer=0;
        for(int i=0;i<n;i++){
            if(visited.find(i)!=visited.end()) continue;
            newConnectedComputer++;
            dfsIter(i);
        }
        
        return newConnectedComputer-1;
    }
};