from typing import List


class Solution:
    def probabilityOfHeads(self, prob: List[float], target: int) -> float:
        dp=[1]+[0]*target
        for p in prob:
            prev=0
            for k in range(0,target+1):
                current=dp[k]
                if k==0:
                    dp[k]=current*(1-p)
                else:
                    dp[k]=prev*p+current*(1-p)
                prev=current
        return dp[target]
    def probabilityOfHeads_neat(self, prob: List[float], target: int) -> float:
        dp=[1]+[0]*target
        for i,p in enumerate(prob):
            for k in range(target,-1,-1):
                if k==0:
                    dp[k]*=1-p
                else:
                    dp[k]=dp[k-1]*p+dp[k]*(1-p)
        return dp[target]

if __name__=="__main__":
    c=Solution()
    print(c.probabilityOfHeads(prob = [0.4], target = 1))#0.4
    print(c.probabilityOfHeads( prob = [0.5,0.5,0.5,0.5,0.5], target = 0))#0.03125
    print(c.probabilityOfHeads([0.2,0.8,0,0.3,0.5],3))#0.182
    print(c.probabilityOfHeads([0.6924087897037671,0.1586882853892071,0.14595606639884107,0.7590888554700622,0.35444894174404573],1))#0.2169