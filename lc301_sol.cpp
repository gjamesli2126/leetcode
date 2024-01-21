class Solution {
public:
    void remove(std::string s, int start, int lastRemove, std::string par, std::vector<std::string>& ans) {
        int stack = 0;
        for (int i = start; i < s.size(); ++i) {
            if (s[i] == par[0]) stack++;
            if (s[i] == par[1]) stack--;
            if (stack >= 0) continue;
            for (int j = lastRemove; j <= i; ++j) {
                if (s[j] == par[1] && (j == lastRemove || s[j - 1] != par[1])) {
                    //This is for duplication when dealing with case like '())'
                    //noted that you are trying out every possible remove of excessive par[1]
                    //so in the above case, both ")" will be checked, but the later one shoudn't 
                    //matter.
                    remove(s.substr(0, j) + s.substr(j+1), i, j, par, ans);                    
                }
            }
            //When you are at this point, stack must < 0, so you have no reason to 
            //Check with the reverse version. So you simply return.
            return;
        }
        //When you are at this point, you only know stack must >= 0.
        //And you only finished left to right checked, with deleting the invalid 
        //parenthesis from left "()())()" ==> you only delete s[1] and checked (())()
        //you haven't find the case of delete s[4] instead. 
        //So at this point, you would need to do the reverse version for the 
        //right to left check!
        std::reverse(s.begin(), s.end());
        
        if (par[0] == '(') {
            //Since we do the reverse anyway, if par[0] is "(", 
            //This will be the case we just checked left to right
            //But not yet right to left
            remove(s, 0, 0, ")(", ans);
        }
        else {
            //We've checked right to left also.
            //And since we reverse string anyway above, we are safe 
            //to put the s into answer.
            
            //** The tricky part is that when we are here, the s must
            //satisfy count of '(' >=  count of ')'
            //as well as count of ')' >= count of '('
            //which means it has '(' == ')', and will be balid answer
            ans.push_back(std::move(s));
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<std::string> ans;
        remove(s, 0, 0, "()", ans);
        return std::move(ans);
    }
};