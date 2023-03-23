import sys
from typing import List
class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n=len(prices)
        if k<n//2:
            t0=[0]*(k+1)# for _ in range(n+1)]
            t1=[-sys.maxsize]*(1+k)# for _ in range(n+1)]
            # t0=0
            # t1=-sys.maxsize
            for price in prices:#n
                for j in range(1,k+1):
                    t0oldTrans=t0[j-1]
                    t0[j]=max(t0[j],t1[j]+price)
                    t1[j]=max(t1[j],t0oldTrans-price)

            return t0[-1]
        else:
            tik0=0
            tik1=-sys.maxsize
            for price in prices:
                tik0old=tik0
                tik1old=tik1
                tik0=max(tik0old,tik1old+price)
                tik1=max(tik1old,tik0old-price)
            return tik0
if __name__=="__main__":
    c=Solution()
    # print(c.maxProfit(k = 2, prices = [2,4,1]))#2
    # print(c.maxProfit( k = 2, prices = [3,2,6,5,0,3]))#7
    # print(c.maxProfit(2,[6,1,3,2,4,7]))#7
    # print("-3 -3 -3 -3 -3 -3 0 2 0 2 0 2 0 2 0 2")
    print(c.maxProfit(2,[3,3,5,0,0,3,1,4]))#6