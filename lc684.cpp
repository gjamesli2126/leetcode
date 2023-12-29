#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n=edges.size();
        vector<int> parent(n,0);
        iota(parent.begin(),parent.end(),1);//element_val: 1 to n
        for(const auto& fs:edges){
            int f=fs[0];
            int s=fs[1];
            //find the root of both f & s
            while(parent[f-1]!=f) f=parent[f-1];
            while(parent[s-1]!=s) s=parent[s-1];
            if(parent[f-1]==parent[s-1]) return vector<int>{fs[0],fs[1]};
            parent[s-1]=f;
        }
        return vector<int>{};
    }
};

