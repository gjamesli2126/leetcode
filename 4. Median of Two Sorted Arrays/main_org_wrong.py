from typing import List
from sys import maxsize
MININT=float('-inf')
MAXINT=float('inf')

def findmean(nums,N):
    if N%2==0:
        return (nums[int((N-1)/2)]+nums[int(N/2)])/2
    else:
        return nums[int(N / 2)]
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        N1=len(nums1)
        N2=len(nums2)
        #
        # if N1==0 and N2==0:
        #     return -1
        # elif N1==0:
        #     return findmean(nums2,N2)
        # elif N2==0:
        #     return findmean(nums1, N1)
        if N1<N2:
            nums2,nums1=nums1,nums2
            N1 = len(nums1)
            N2 = len(nums2)
        lo=0
        hi=N2
        while lo<=hi:
            # cut1=(lo+hi)/2
            # cut2=(N1+N2)/2-cut1
            cut2=(lo+hi)/2
            cut1=N1+N2-cut2

            #L1
            if cut1==0 :
                L1=MININT
            else:
                L1=nums1[int((cut1-1)/2)]

            #R1
            if cut1==2*N1:
                R1=MAXINT
            else:
                R1=nums1[int(cut1/2)]

            #L2
            if cut2==0 :
                L2=MININT
            else:
                L2=nums2[int((cut2-1)/2)]

            #R2
            if cut2==2*N2:
                R2=MAXINT
            else:
                R2=nums2[int(cut2/2)]


            if L1>R2:
                lo=cut1-1
            elif L2>R1:
                hi=cut2-1
            else:
                return (max(L1,L2)+min(R1,R2))/2
        return -1




if __name__=="__main__":
    c=Solution()
    print(c.findMedianSortedArrays([1,3],[2]))#2
    print(c.findMedianSortedArrays([1, 2], [3,4]))  # 2.5
    print(c.findMedianSortedArrays([], [2,3]))  # 2.5
    print(c.findMedianSortedArrays([3], [-2, -1]))  # -1

    print(c.findMedianSortedArrays([3,4], []))  # -1