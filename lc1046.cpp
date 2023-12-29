#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        make_heap(stones.begin(),stones.end());
        while(stones.size()>1){
            //give out first 2 large stone
            int s1=stones.front();
            pop_heap(stones.begin(),stones.end());
            stones.pop_back();
            int s2=stones.front();
            pop_heap(stones.begin(),stones.end());
            stones.pop_back();
            
            //put back the after-crash
            stones.push_back(s1-s2);
            push_heap(stones.begin(),stones.end());
        }
        if(stones.empty()) return 0;
        else return stones[0];
    }
};