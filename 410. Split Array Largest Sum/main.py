


def new_mid(middle, nums, m):
    count = 1
    total = 0
    for i in nums:
        total += i
        if (total > middle):
            total = i
            count = count + 1
        if (count > m):
            return False
    return True

def splitArray(nums, m):
    right = sum(nums)
    left = max(nums)

    while (left <= right):
        middle = left + (right - left) // 2
        if (new_mid(middle, nums, m)):
            right = middle -1
        else:
            left = middle + 1
    return left

if __name__ =="__main__":
    nums=[3,9,6,7,8,11,1,4,7]
    m=4
    ans=splitArray(nums,m)
    print(ans)