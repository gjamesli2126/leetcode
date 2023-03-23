from typing import List
class Solution:
    def validWordAbbreviation(self, word: str, abbr: str) -> bool:
        wordPtr=0
        number=0
        for ind,a in enumerate(abbr):
            if a.isnumeric():
                if int(a)==0 and (ind==0 or abbr[ind-1].isnumeric()==False):
                    return False
                else:
                    number=10*number+int(a)
            else:
                if wordPtr<len(word) and number>0:
                    wordPtr+=number
                    number=0
                if wordPtr<len(word) and a==word[wordPtr]:
                    wordPtr+=1
                else:
                    return False
        return True if len(word)-wordPtr==number else False
if __name__=="__main__":
    c=Solution()
    print(c.validWordAbbreviation(word = "internationalization", abbr = "i12iz4n"))#T
    print(c.validWordAbbreviation(word = "apple", abbr = "a2e"))#F
    print(c.validWordAbbreviation("azsdxd",abbr="a1s0dxd"))#F
    print(c.validWordAbbreviation(abbr="asd10",word="asdqwsasdewer"))#T
    print(c.validWordAbbreviation(abbr="asd10", word="asdq"))  # T
    print(c.validWordAbbreviation(abbr="aa10a", word="aaaaaaaaaaaaa"))  # T
    print(c.validWordAbbreviation("a","2"))#F
    print(c.validWordAbbreviation("a", "1"))  # T
    print(c.validWordAbbreviation("internationalization","i5a11o1"))#T
    print(c.validWordAbbreviation("hi","2i"))#F
