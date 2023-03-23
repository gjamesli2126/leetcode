from typing import List
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        if target<nums[0]:
            return 0
        down=0
        up=len(nums)-1
        while down<=up:
            mid=(down+up)//2
            midV=nums[mid]

            if midV==target:# or (midV<target and (mid<len(nums)-1 and target<nums[mid+1])):
                return mid
            elif midV<target:
                if  (mid<len(nums)-1 and target<nums[mid+1]):
                    return mid + 1
                elif mid==len(nums)-1:
                    return mid+1


            if target<midV:
                up=mid
            else:
                down=mid+1
        return -1
if __name__=="__main__":
    c=Solution()
    print(c.searchInsert(nums = [1,3,5,6], target = 5))#2
    print(c.searchInsert(nums = [1,3,5,6], target = 2)) #1
    print(c.searchInsert(nums = [1,3,5,6], target = 7))#4
    print(c.searchInsert(nums=[1, 3, 5, 6], target=0))  # 2