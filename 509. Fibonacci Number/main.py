class Solution:
    def fib(self, n: int) -> int:
        if n==1 or n==0:
            return n
        elif n<=4:
            return n-1
        prev=1
        oldest=0
        for i in range(2,n+1):
            current=prev+oldest
            oldest=prev
            prev=current
            # print(current)
        return current

if __name__=="__main__":
    c=Solution()
    print(c.fib(2))#1
    print(c.fib(3))#2
    print(c.fib(4))#3
    print(c.fib(5))#5
    print(c.fib(6))#8
    print(c.fib(7))#13