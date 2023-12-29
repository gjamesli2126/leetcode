#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {
         vector<int> dp(maxLength+1);

         dp[0]=1;
         for(int i=1;i<=maxLength;++i){

             if(i>=oneGroup) dp[i]+=dp[i-oneGroup];
             dp[i]%=static_cast<long long>(pow(10,9)+7);
             if(i>=zeroGroup) dp[i]+=dp[i-zeroGroup];
             dp[i]%=static_cast<long long>(pow(10,9)+7);
         }
         return accumulate(dp.begin()+minLength,dp.begin()+maxLength+1,0LL)%static_cast<long long>(pow(10,9)+7);
    }
};