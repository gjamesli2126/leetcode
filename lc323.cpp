#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
    unordered_map<int,unordered_set<int>> dict;
    unordered_set<int> visited;
public:
    void dfs(int node){
        stack<int> stk;
        stk.push(node);
        while(!stk.empty()){
            int n=stk.top();
            stk.pop();
            visited.insert(n);
            for(const int& nxt:dict[n]){
                if(visited.find(nxt)==visited.end()){
                    stk.push(nxt);
                }
            }
        }
    }
    int countComponents(int n, vector<vector<int>>& edges) {
        //build the damn graph
        for(const vector<int>& v:edges){
            dict[v[0]].insert(v[1]);
            dict[v[1]].insert(v[0]);
        }
        int islandNum=0;
        for(int i=0;i<n;i++){
            if(visited.find(i)!=visited.end()) continue;
            islandNum++;
            for(const int& nxt:dict[i]) dfs(nxt);
        }
        return islandNum;
    }
};