from typing import List
from sys import maxsize
# MININT=int(-maxsize)
# MAXINT=int(maxsize)
MININT=float('-inf')
MAXINT=float('inf')
class Solution:
    def findMedianSortedArrays(self, a1: List[int], a2: List[int]) -> float:
        n1=len(a1)
        n2=len(a2)
        if n1>n2:
            a1,a2=a2,a1
            n1 = len(a1)
            n2 = len(a2)
        lo=0
        hi=n1
        while lo<=hi:
            cut1=int((lo+hi)/2)
            cut2=int((n1+n2)/2-cut1)
            l1=MININT if cut1==0 else a1[cut1-1]
            l2=MININT if cut2==0 else a2[cut2-1]
            r1=MAXINT if cut1==n1 else a1[cut1]
            r2=MAXINT if cut2==n2 else a2[cut2]
            if l1>r2:
                hi=cut1-1
            elif l2>r1:
                lo=cut1+1
            else:
                return min(r1,r2) if (n1+n2)%2 else (max(l1,l2)+min(r1,r2))/2




if __name__=="__main__":
    c=Solution()
    print(c.findMedianSortedArrays([1,3],[2]))#2
    print(c.findMedianSortedArrays([1, 2], [3,4]))  # 2.5
    print(c.findMedianSortedArrays([], [2,3]))  # 2.5
    print(c.findMedianSortedArrays([3], [-2, -1]))  # -1
    print(c.findMedianSortedArrays([3,4], []))  # -1

