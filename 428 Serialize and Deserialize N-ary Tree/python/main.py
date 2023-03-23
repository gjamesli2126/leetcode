# Definition for a Node.
class Node(object):
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children

class Codec:
    def serialize(self, root: 'Node') -> str:
        str0=root.val
        Q=[]
        for node in root.children:
            if node.children:
                
            else:
                str0+=node.val

    def deserialize(self, data: str) -> 'Node':
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: Node
        """

# Your Codec object will be instantiated and called as such:
codec = Codec()
# codec.deserialize(codec.serialize(root))

root=Node(1,[])
root.children.append(Node(2,[]))
root.children.append(Node(3,[]))
root.children.append(Node(4,[]))
root.children[2].append(Node(8,[]))
root.children.append(Node(5,[]))
root.children[1].children.append(Node(6,[]))
root.children[1].children.append(Node(7,[]))


print(codec.serialize(root))
