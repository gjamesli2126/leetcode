from typing import List
import re
class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        ans= re.search(needle,haystack)
        return ans.start() if ans else -1
if __name__=="__main__":
    c=Solution()
