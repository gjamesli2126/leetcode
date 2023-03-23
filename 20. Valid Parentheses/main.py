from collections import deque
class Solution:
    def isValid(self, s: str) -> bool:
        d={"{":"}","[":"]","(":")"}
        stack=deque([])
        invalid=False
        for e in s.replace(" ",""):
            if e in d.keys():
                stack.append(e)
            elif stack:
                popready=stack[-1]# 最後進來的人
                if d[popready]==e:
                    stack.pop()
                else:
                    invalid = True
            else:
                invalid=True
        return not stack and not invalid
if __name__=="__main__":
    c=Solution()
    print(c.isValid("{ { } [ ] [ [ [ ] ] ] } "))#T
    print(c.isValid("{ { ( { } ) } }"))#T
    print(c.isValid("()[]{}"))#T
    print(c.isValid("]")) #F
    print(c.isValid("(])")) #F