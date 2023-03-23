"""
# Definition for a Node.
class Node(object):
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""
from collections import deque



class Codec:
    def serialize(self, root: 'Node') -> str:
        """Encodes a tree to a single string.

        :type root: Node
        :rtype: str
        """
        def serializeHelper(res, curr):

            if curr == None:
                return res


            res = res + str(curr.val) + ','

            for child in curr.children:
                res = serializeHelper(res, child)
            return res + 'p,'


        res = serializeHelper('', root)

        return res




    def deserialize(self, data: str) -> 'Node':
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: Node
        """
        ls = data.split(',')
        stack = deque()

        if ls[0] == '':
            return None

        root = par = Node(int(ls[0]), [])

        for val in ls[1:]:
            if val == '':
                continue

            if val == 'p':
                if not stack: # if stack were empty
                    return root
                else:
                    par = stack.pop()

            else:
                newChild = Node(int(val), [])
                par.children.append(newChild)
                stack.append(par)
                par = newChild


        return root




# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.deserialize(codec.serialize(root))