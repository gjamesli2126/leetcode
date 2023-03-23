from collections import deque
class TrieNode:
    def __init__(self,isWord=False):
        self.isWord = isWord
        self.children = {}  # Charc:Node
class Trie:
    def __init__(self):
        self.root=TrieNode()
    def insert(self, word: str) -> None:
        if not word:
            return
        node=self.root
        word=deque(word)
        while True:
            charc=word.popleft()
            if charc in node.children.keys():
                node=node.children[charc]
                if not word:
                    node.isWord = True
                    break
            else:
                node.children[charc]=TrieNode()
                if not word:
                    if node.children[charc]:
                        node.children[charc].isWord=True
                    else:
                        node.children[charc]=TrieNode(True)
                    break
                else:
                    node=node.children[charc]
    def search(self, word: str) -> bool:
        if not word:
            return False
        node=self.root
        word=deque(word)
        while True:
            charc=word.popleft()
            if charc in node.children.keys():
                node=node.children[charc]
            else:
                return False
            if not word:
                return node.isWord
    def startsWith(self, prefix: str) -> bool:
        node=self.root
        prefix=deque(prefix)
        while True:
            charc=prefix.popleft()
            if charc in node.children.keys():
                node=node.children[charc]
            else:
                return False
            if not prefix:
                return True
if __name__=="__main__":
    # Your Trie object will be instantiated and called as such:
    trie = Trie()
    trie.insert("apple")
    print(trie.search("apple"))# return True
    print(trie.search("app")) # return False
    print(trie.startsWith("app"))#; // return True
    trie.insert("app")
    print(trie.search("app"))#; // return True