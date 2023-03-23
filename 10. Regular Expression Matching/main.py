from typing import List
import re
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        if not s or not p:
            return False

    #     return re.match("".join(["^", p, "$"]), s)


if __name__=="__main__":
    c=Solution()
