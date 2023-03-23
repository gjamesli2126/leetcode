from typing import List
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        negative= (dividend<0) and (divisor>0) or (dividend>0) and (divisor<0)
        dividend=abs(dividend)
        divisor=abs(divisor)
        stack=[]
        q=0
        res=dividend
        while divisor<=res:
           res-=divisor
           q+=1

        if negative:
            q*=-1
        return q

if __name__=="__main__":
    c=Solution()
    print(c.divide(10,3))#3
    print(c.divide(7,-3))#-2
    print(c.divide(-2147483648,-1))