#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isPalindrome(const string& s) {
        int p1=0,p2=s.length()-1;    
        while(p1<=p2){
            char c1=s[p1];
            char c2=s[p2];
            while(!isalnum(c1) && p1<p2) c1=s[++p1];
            while(!isalnum(c2) && p1<p2) c2=s[--p2];
            assert((!isalnum(c1) || !isalnum(c2))==(!isalnum(c1) && !isalnum(c2)));
            if(!isalnum(c1) || !isalnum(c2)) return true;// p1 p2 came accross && both are not alnum
            if(tolower(c1)!=tolower(c2)) return false;
            p1++;
            p2--;
        }
        return true;
    }
};