#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
//    struct pairHash{
//        template<class T1,class T2>
//        size_t operator()(const pair<T1,T2>& p) const{
//            auto h1=hash<T1>{}(p.first);
//            auto h2=hash<T2>{}(p.second);
//            return h1^(h2*31);
//        }
//    };
    vector<vector<string>> ans;
    unordered_set<int> cols,postDiag,negDiag;
    int N;
    void dfsBackTrack(int r,vector<string>& cur){
        if(r==N){
            ans.push_back(cur);
            return;
        }
        for(int c=0;c<N;++c){
            if(cols.contains(c) || postDiag.contains(r+c) || negDiag.contains(r-c)) continue;
            //add
            cur[r][c]='Q';
            cols.insert(c);
            postDiag.insert(r+c);
            negDiag.insert(r-c);
            dfsBackTrack(r+1,cur);
            //don't add
            cur[r][c]='.';
            cols.erase(c);
            postDiag.erase(r+c);
            negDiag.erase(r-c);
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        if(n==1) return {{"Q"}};
        N=n;
        vector<string> initV(n,string(n,'.'));
        dfsBackTrack(0,initV);
        return ans;
    }
};

