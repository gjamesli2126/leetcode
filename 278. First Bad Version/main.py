# The isBadVersion API is already defined for you.
def isBadVersion(version: int) -> bool:
    return version>=3

class Solution:
    def firstBadVersion(self, n: int) -> int:
        if n==1:
            return 1
        # elif n==2:
        #     if not isBadVersion(1):
        #         return 2
        #     else:
        #         return 1
        downInd=0
        upInd=n
        while downInd<=upInd:
            midInd=(upInd+downInd)//2
            if isBadVersion(midInd) and not isBadVersion(midInd-1):
                return midInd
            if isBadVersion(midInd):
                upInd=midInd-1
            else:
                downInd=midInd+1
        return -1


if __name__=="__main__":
    c=Solution()
    print(c.firstBadVersion(3))
