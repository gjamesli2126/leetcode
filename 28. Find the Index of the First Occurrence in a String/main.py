from typing import List

class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        for i,h in enumerate(haystack):
            if h==needle[0]:
                if needle==haystack[i:i+len(needle)]:
                    return i
        return -1
if __name__=="__main__":
    c=Solution()
