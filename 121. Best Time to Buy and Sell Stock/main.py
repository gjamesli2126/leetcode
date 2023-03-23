from typing import List

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        suggestBuy=prices[0]
        profit=0
        for rptr,suggestSell in enumerate(prices[1:]):
            if suggestSell>suggestBuy:
                profit=max(profit,suggestSell-suggestBuy)
            elif suggestSell<suggestBuy:
                suggestBuy=suggestSell
        return profit
# class Solution:
#     def maxProfit(self, prices: List[int]) -> int:
#         lptr = 0
#         profit=0
#         for rptr,price in enumerate(prices):
#             if price>prices[lptr]:
#                 profit=max(profit,price-prices[lptr])
#             else:
#                 lptr=rptr
#
#         return profit
if __name__=="__main__":
    c=Solution()
    print(c.maxProfit(prices = [7,1,5,3,6,4]))#5
    print(c.maxProfit(prices = [7,6,4,3,1]))#0
