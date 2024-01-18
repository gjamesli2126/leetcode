/*
 Given an m x n binary matrix, return the distance of the nearest 0 for each cell.
 The distance between two adjacent cells is 1.
*/
#include<bits/stdc++.h>
class Solution{
private:
    std::vector<std::vector<int>> ans;
    int maxR,maxC;
public:
    std::vector<std::vector<int>> giveMeAns(std::vector<std::vector<int>>& v){
        if(v.empty()) return {{}};
        maxR=v.size();
        maxC=v[0].size();

        return ans;
    }
};