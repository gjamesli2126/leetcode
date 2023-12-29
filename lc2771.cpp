#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int i;
        size_t s=nums1.size();
        int maxFrom1=1;
        int maxFrom2=1;
        int tran11,tran12,tran21,tran22;//1->1,1->2,....
        int maxCount=1;
        for(i=1;i<s;i++){
            tran11=nums1[i-1]<=nums1[i]? maxFrom1+1:1;
            tran12=nums1[i-1]<=nums2[i]? maxFrom1+1:1;
            tran21=nums2[i-1]<=nums1[i]? maxFrom2+1:1;
            tran22=nums2[i-1]<=nums2[i]? maxFrom2+1:1;
            maxFrom1=max(tran21,tran11);
            maxFrom2=max(tran22,tran12);
            maxCount=max({maxCount,maxFrom1,maxFrom2});// 可能曾經一度最高
        }
        return maxCount;
    }
};