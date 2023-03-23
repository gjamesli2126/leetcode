from typing import List
import sys

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        tik0=0
        tik1=-sys.maxsize
        ti_2k0=0

        for price in prices:
            ti_1k0=tik0
            tik0=max(tik0,tik1+price)
            tik1=max(tik1,ti_2k0-price)
            ti_2k0=ti_1k0
        return tik0
if __name__=="__main__":
    c=Solution()
    print(c.maxProfit( prices = [1,2,3,0,2]))#3
    print(c.maxProfit([1]))#0