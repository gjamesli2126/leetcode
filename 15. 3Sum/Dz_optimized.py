from typing import List


class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        res = []
        nums.sort()
        v1 = None
        for i in range(0, len(nums) - 2):
            if v1 is not None and nums[i] == v1:
                continue
            v1 = nums[i]
            for pair in twoSum(nums=nums, l=i + 1, r=len(nums) - 1, target=0 - v1):
                res.append([v1, pair[0], pair[1]])
        return res

def twoSum(nums, l, r, target):
    res = []
    while l < r:
        v2, v3 = nums[l], nums[r]
        sum_val = v2 + v3
        if sum_val == target:
            res.append([nums[l], nums[r]])
            while l < r and nums[l] == v2:
                l += 1
            while l < r and nums[r] == v3:
                r -= 1
        elif sum_val > target:
            r -= 1
        else:
            l += 1
    return res