
class Solution:
    def climbStairs(self, n: int) -> int:
        if n<=3:
            return n
        oldest=1
        old=1
        for _ in range(n-1):
            current=old+oldest
            oldest = old
            old=current

        return current
if __name__=="__main__":
    c=Solution()
    print(c.climbStairs(2))#2
    print(c.climbStairs(3))  # 3
    print(c.climbStairs(4))  # 5
    print(c.climbStairs(5))  # 8
    # for i in range(10):
    #     print(c.climbStairs(i))