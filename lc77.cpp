/*
 * [1,2,3,4,5,6]
 * k=2
 * [3,4],[1,2]....
 * */
#include <bits/stdc++.h>
using namespace std;
class Solution{
private:
    vector<vector<int>> ans;
    int N;
    void dfs(int k,vector<int>& cur,int i){
//        if(N-i<k) return;
        if(!k){
            ans.push_back(cur);
            return;
        }
        // 0,1,2,3,4,5,6
        for(int ind=i;ind<=N-k+1;++ind){
            cur.push_back(ind);
            dfs(k-1,cur,ind+1);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combine(const int& n,const int& k){
        if(k>n) return {{}};
        N=n;
        vector<int> emptyCur;
        dfs(k,emptyCur,1);
        return ans;
    }
};
