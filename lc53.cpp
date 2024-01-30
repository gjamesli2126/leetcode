#include<bits/stdc++.h>
using namespace std;
#define mainTest main

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int globalMax=-10000;
        int localMax=-10000;
        for(const int n:nums){
            localMax=max(localMax+n,n);
            globalMax= max(globalMax,localMax);
        }
        return globalMax;
    }
};