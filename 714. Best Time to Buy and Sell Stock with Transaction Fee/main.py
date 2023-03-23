from typing import List
import sys

class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        tik0=0
        tik1=-sys.maxsize
        for price in prices:
            tik0Old=tik0
            tik1Old=tik1
            tik0=max(tik0,tik1Old+price)#after sell
            tik1=max(tik1,tik0Old-price-fee)#after buy
            print(tik0,tik1)
        return tik0
if __name__=="__main__":
    c=Solution()
    print(c.maxProfit(prices = [1,3,2,8,4,9], fee = 2))#8
    # print(c.maxProfit(prices = [1,3,7,5,10,3], fee = 3))#6