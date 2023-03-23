from typing import List, Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        carry=0
        orgl1=l1
        orgl2=l2
        long=None
        last=None
        while l1 or l2:
            n1=l1.val if l1 else 0
            n2 = l2.val if l2 else 0

            s=n1+n2+carry
            carry=int(s>=10)
            if l1:
                l1.val = s % 10
                last = l1
                l1=l1.next

                long = orgl1
            if l2:
                l2.val=s%10
                last = l2
                l2 = l2.next
                long = orgl2
        if carry:
            last.next=ListNode(carry)
        return long




if __name__=="__main__":
    c=Solution()

