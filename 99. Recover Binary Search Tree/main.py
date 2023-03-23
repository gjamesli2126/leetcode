from typing import List, Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def recoverTree(self, root: Optional[TreeNode]) -> None:
        x=None
        y=None
        previous_visited=None
        def dfs(root):
            nonlocal x,y,previous_visited
            if root is None: return
            dfs(root.left)
            if previous_visited and root.val<previous_visited.val:
                y=root
                if x is None: x=previous_visited#first occurance
                else:return #second occurance
            previous_visited=root
            dfs(root.right)
        dfs(root)
        x.val,y.val=y.val,x.val



if __name__=="__main__":
    c=Solution()
