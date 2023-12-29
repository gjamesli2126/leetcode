#include<bits/stdc++.h>
using namespace std;
class Solution {
private:
    static unsigned long long& fracFn(const int& n){
        static int maxN=0;
        static array<unsigned long long,27> fracTable;
        fracTable[0]=1;
        if(n>maxN){
            while(maxN<=n){
                ++maxN;
                fracTable[maxN] = (static_cast<unsigned long long>(fracTable[maxN - 1]) * maxN);// % 1000000007;
                // cout<<maxN<<": "<<fracTable[maxN]<<endl;
            }
        }
        return fracTable[n];
    }
    unsigned long long eachPermutation(const string& s){
        unordered_map<char,int> mp;
        for(const char& c:s){
            if(mp.find(c)==mp.end()) mp[c]=1;
            else mp[c]++;
        }
        unsigned long long frac=fracFn(static_cast<int>(s.size()));
        for(const auto& [_,f]:mp) frac/=fracFn(f);
        
        return frac;
    }
public:
    int countAnagrams(string s) {
        istringstream ss(s);
        unsigned long long ans=1;
        string word;
        while(ss>>word){
            ans*=static_cast<unsigned long long>(eachPermutation(word))%1000000007;
            ans%=1000000007;
            
        }
        
        return static_cast<int>(ans);
    }
};



/* 
a~z && freq=f1,f2,.....,f26
Then permutation=26!/(f1!*f2!*f3!*....*f26!)
*/

/*
You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.

A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.

For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "too hot"
Output: 18
Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
Example 2:

Input: s = "aa"
Output: 1
Explanation: There is only one anagram possible for the given string.
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters and spaces ' '.
There is single space between consecutive words.

*/