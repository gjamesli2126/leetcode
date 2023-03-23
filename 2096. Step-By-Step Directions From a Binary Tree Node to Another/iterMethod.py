from collections import deque
from typing import List, Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def find(self, value, root,path)->bool:
        stack=deque()
        stack.append(root)
        found=False
        visited=set()
        shouldMarked=set()
        while stack:
            node=stack[-1]
            if value==node.val:
                visited.add(node)
                shouldMarked.add(node)
                stack.pop()
                found|=True

            elif found and node.left in shouldMarked:
                path.append('L')
                visited.add(node.left)
                shouldMarked.add(node)
                stack.pop()
            elif node.left and node.left not in visited:
                stack.append(node.left)

            elif found and node.right in shouldMarked:
                path.append('R')
                visited.add(node.right)
                shouldMarked.add(node)
                stack.pop()
            elif node.right and node.right not in visited:
                stack.append(node.right)

            else:
                visited.add(node)
                stack.pop()

        return found
    def getDirections(self, root: Optional[TreeNode], startValue: int, destValue: int) -> str:
        startPath=[]
        destPath = []
        if self.find(startValue,root,startPath) and self.find(destValue,root,destPath):
            while startPath and destPath and startPath[-1]==destPath[-1]:
                startPath.pop()
                destPath.pop()
            startStr="".join(len(startPath)*'U')
            destStr="".join(reversed(destPath))
            return startStr+destStr
if __name__=="__main__":
    c=Solution()
    root1=TreeNode(5)
    root1.right=TreeNode(2)
    root1.right.left=TreeNode(6)
    root1.right.right = TreeNode(4)
    root1.left=TreeNode(1)
    root1.left.left=TreeNode(3)
    print(c.getDirections(root = root1, startValue = 3, destValue = 6))#UURL
    root2=TreeNode(2)
    root2.left=TreeNode(1)
    print(c.getDirections( root = root2, startValue = 2, destValue = 1))#L
    root3=TreeNode(3)
    root3.left=TreeNode(1)
    root3.right = TreeNode(2)
    print(c.getDirections(root3,2,1))#UL
