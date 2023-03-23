# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import copy

def minDifference(nums0):
    if len(nums0)<=1:
        return 0
    nums=copy.deepcopy(nums0)
    minmax4=[]

    if len(nums)>=8:
        for _ in range(4):
            minv=min(nums)
            maxv = max(nums)
            nums.remove(maxv)
            nums.remove(minv)
            minmax4.append(minv)
            minmax4.append(maxv)

    else:
        for _ in nums:
            minv=min(nums)
            maxv = max(nums)
            nums.remove(maxv)
            nums.remove(minv)
            minmax4.append(minv)
            minmax4.append(maxv)
    minoutput=10**9
    for guess in minmax4:
        nums = copy.deepcopy(nums0)
        for ind,n in enumerate(nums):
            if n in minmax4:
                nums[ind]=guess






# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    minDifference([1,5,0,10,14])

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
