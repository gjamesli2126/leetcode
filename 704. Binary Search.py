class Solution:
    def search(self, nums: list, target: int) -> int:
        if len(nums)==0:
            return -1
        else:
            L=0
            H=len(nums)-1

            while L<=H:

                pivot = int((L + H) / 2)
                # print(L, H, pivot)
                if target>nums[pivot]:
                    L=pivot+1
                elif target<nums[pivot]:
                    H=pivot-1
                elif target==nums[pivot]:
                    return pivot
                else:
                    return -1
            return -1
if __name__ =="__main__":
    C=Solution()
    print(C.search(nums=[-1,0,3,5,9,12], target = 9))
    print(C.search(nums = [-1,0,3,5,9,12], target = 2))