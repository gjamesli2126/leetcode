from typing import List, Optional
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def find(self, value, node,path)->bool:
        # print(node.val)
        if value==node.val:
            return True
        elif not node:
            return False
        elif node.left and self.find(value, node.left,path):
            path.append('L')
            return True
        elif node.right and self.find(value, node.right,path):
            path.append('R')
            return True
        return False
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
