class Solution {
public:
    int minOperations(int n) {
        //if single bit then +1 else +2
        int res=0;
        while(n>0){
            if((n&0b11)==0b11){
                n++;
                res++;
            }
            else{
                res+=n&1;
                n>>=1;
            }
        }
        return res;
    }
};