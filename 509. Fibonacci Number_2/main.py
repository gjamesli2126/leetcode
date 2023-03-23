class Solution:
    def fib(self, n: int) -> int:
        if n==0:
            return 0
        elif n<=2:
            return 1
        elif n<=4:
            return n-1
        oldest=0
        old=1

        for _ in range(n-1):
            current=old+oldest
            oldest=old
            old=current
        return current



if __name__=="__main__":
    c=Solution()
    print(c.fib(2))#1
    print(c.fib(3))#2
    print(c.fib(4))#3
    print(c.fib(5))#5
    print(c.fib(6))#8
    print(c.fib(7))#13
