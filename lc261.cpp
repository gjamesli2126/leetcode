#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size()+1!=n) return false;
        //用union find 若無loop && edge數==node數-1 Then true else false
        vector<int> parent(n,0);
        iota(parent.begin(),parent.end(),0);
        for(const auto& p:edges){
            int f=p[0];
            int s=p[1];
            //find the root(parent's parent's ...) of the first node
            while(parent[f]!=f) f=parent[f];
            //find the root(parent's parent's ...) of the second node
            while(parent[s]!=s) s=parent[s];
            if(parent[f]==parent[s]) return false;//if f & s are on the same graph && f-s want to form an edge -> cycle must happen!!!!
            parent[s]=f;//form the edge
        }
       return true;
         
        
    }
};