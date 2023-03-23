class Solution:
    def tribonacci(self, n: int) -> int:
        if n<=1:
            return n
        elif n==2:
            return 1

        tn=0
        tn1=1
        tn2=1
        for i in range(3,n+1):
            tn3=tn+tn1+tn2
            tn=tn1
            tn1=tn2
            tn2=tn3
        return tn3

if __name__=="__main__":
    c=Solution()
    print(c.tribonacci(4))#4
    print(c.tribonacci(25))#1389537