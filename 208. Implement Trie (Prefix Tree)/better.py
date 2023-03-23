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
        for charc in word:
            if charc not in node.children.keys():
                node.children[charc]=TrieNode()
            node=node.children[charc]
        node.isWord=True

    def search(self, word: str) -> bool:
        if not word:
            return False
        node=self.root
        for charc in word:
            if charc not in node.children.keys():
                return False
            else:
                node=node.children[charc]
        return node.isWord

    def startsWith(self, prefix: str) -> bool:
        if not prefix:
            return False
        node=self.root
        for charc in prefix:
            if charc not in node.children.keys():
                return False
            else:
                node=node.children[charc]
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