from typing import List, Optional
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head is None:
            return None
        elif head.next==head:
            return head

        #Let fast & slow ptr meet
        fastPtr=head
        slowPtr=head
        met=None
        while fastPtr.next and fastPtr.next.next and slowPtr.next:
            fastPtr=fastPtr.next.next
            slowPtr=slowPtr.next
            if fastPtr==slowPtr:
                met=fastPtr
                break
        if not met:
            return None
        #Count cycle length
        traverse=met.next
        count=1
        while traverse!=met:
            traverse=traverse.next
            count+=1
        #return the cycle offset
        fastPtr=head
        slowPtr=head
        for _ in range(count):
            fastPtr=fastPtr.next
        while slowPtr!=fastPtr:
            slowPtr=slowPtr.next
            fastPtr=fastPtr.next
        return slowPtr
if __name__=="__main__":
    c=Solution()
    n=ListNode(3)
    n.next=ListNode(2)
    n.next.next=ListNode(0)
    n.next.next.next= ListNode(-4)
    n.next.next.next.next=n.next
    print(c.detectCycle(n).val)#2

    n=ListNode(1)
    print(c.detectCycle(n))  # None



