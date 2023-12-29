#include <bits/stdc++.h>
using namespace std;
struct pair_hash{
    size_t operator()(const pair<int,int> &pr) const {// must need const here!
        size_t hash1=hash<int>{}(pr.first);
        size_t hash2=hash<int>{}(pr.second);
        return hash1^(hash2<<1);
    }
};
class Solution {
private:

    unordered_map<pair<int,int>,int,pair_hash> coordSteps;

    int dfs(int x,int y){
        if(coordSteps.find({x,y})!=coordSteps.end()){
           return coordSteps[{x,y}];
        }
        else if(x+y==0) return 0;
        else if(x+y==2) return 2;
        else{
            coordSteps[{x,y}]=min(dfs(abs(x-1),abs(y-2)),dfs(abs(x-2),abs(y-1)))+1;
            return coordSteps[{x,y}];
        }
    }
public:
    int minKnightMoves(int x, int y) {
        return dfs(abs(x),abs(y));
    }
};