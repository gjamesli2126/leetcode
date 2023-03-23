from typing import List


class Solution1:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        k %= n
        startIndex=0
        count=0
        while count<n:
            currentIndex=startIndex
            prevVal=nums[startIndex]
            while True:
                currentIndex+=k
                currentIndex%=n
                nums[currentIndex],prevVal=prevVal,nums[currentIndex]
                count+=1
                if currentIndex==startIndex:
                    break
            startIndex+=1
        print(nums)
class Solution:
    def _reverse(self,org,headInd,tailInd):
        while headInd<tailInd:
            org[headInd],org[tailInd]=org[tailInd],org[headInd]
            headInd+=1
            tailInd-=1
    def rotate(self, nums: List[int], k: int) -> None:
        n=len(nums)
        k%=n
        #reverse all
        self._reverse(nums,0,n-1)
        #reverse before k part
        self._reverse(nums,0,k-1)
        #reverse after k part
        self._reverse(nums,k,n-1)
        print(nums)
if __name__=="__main__":
    c=Solution()
    c.rotate(nums = [100,200,300,400,500,600,700], k = 3) #[5,6,7,1,2,3,4]
    c.rotate(nums = [-1,-100,3,99], k = 2)#[3,99,-1,-100]