import math


class Solution:
    def myPow(self, x: float, n: int) -> float:
        if x==0 or x==1: return x
        elif n==0: return 1
        minus=True if n<0 else False
        ans=1
        n=abs(n)
        pw = n
        currentProduct=x
        while pw>=1:
            if pw%2==1:
                ans*=currentProduct # 要多乘一個 currentProduct
            print(pw,ans,currentProduct)
            currentProduct*=currentProduct
            pw//=2
        return 1/ans if minus else ans

if __name__=="__main__":
    c=Solution()
    # print(c.myPow(2,10))#1024
    print(c.myPow(2,19))#524288
    # print(c.myPow(2.1,3))#9.26100
    # print(c.myPow(2,-2))#0.25
    # print(c.myPow(1,-2147483648)) #1
    # print(c.myPow(2, -2147483648))  # 0