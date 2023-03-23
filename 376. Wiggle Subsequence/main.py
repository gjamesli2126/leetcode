from typing import List


class Solution:
    def classsify(self,num1,num2):
        if num1>num2:
            return 0
        elif num1==num2:
            return 1
        else:
            return 2
    def wiggleMaxLength(self, nums: List[int]) -> int:
        if len(nums)==1:
            return 1
        times=0
        # lastStatus=False if nums[1]-nums[0]>0 else True
        lastStatus = self.classsify(nums[1],nums[0])
        if nums[1]!=nums[0]:
            times+=1
        for i,num in enumerate(nums[2:]):
            if num==nums[i+1]:
                continue
            thisStatus=self.classsify(num,nums[i+1])
            times+=1 if lastStatus!=thisStatus else 0
            lastStatus = thisStatus
        return times+1
if __name__=="__main__":
    c=Solution()
    print(c.wiggleMaxLength(nums = [1,7,4,9,2,5]))#6
    print(c.wiggleMaxLength(nums = [1,17,5,10,13,15,10,5,16,8]))#7
    print(c.wiggleMaxLength(nums = [1,2,3,4,5,6,7,8,9]))#2
    print(c.wiggleMaxLength(nums=[1, 2, 3,3,3,3, 4, 5, 6,6,6, 7, 8, 9]))  # 2
    print(c.wiggleMaxLength(nums=[2, 1, 3, 4, 5, 6, 7, 8, 9]))  # 3
    print(c.wiggleMaxLength([0,0]))#1
    print(c.wiggleMaxLength([0,0,0,0,0]))#1
    print(c.wiggleMaxLength([0, 0, 0, 0, -1,0]))  # 3
    print(c.wiggleMaxLength([0, 0, 0, 0, 1, 0]))  # 3
    print(c.wiggleMaxLength([3,3,3,3,2,5]))#3