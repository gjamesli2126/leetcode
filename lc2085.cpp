#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    unordered_map<string,int> mp1;
    unordered_map<string ,int> mp2;
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        mp1.reserve(words1.size());
        mp2.reserve(words2.size());
        for(const auto &s:words1) ++mp1[s];
        for(const auto &s:words2) ++mp2[s];
        int count=0;
        for(const auto &[k,v]:mp1){
            if(v!=1 || mp2.find(k)==mp2.end() || mp2[k]!=1) continue;
            ++count;
        }
        return count;
    }
};