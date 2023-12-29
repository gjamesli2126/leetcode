class Solution {
public:
    vector<vector<int>> graph;//(numCourses,vector<int>{});
    vector<bool> taken;
    unordered_set<int> visiting;
    
    bool dfs(int i){
        if(taken[i]) return true;
        bool ans=true;
        visiting.insert(i);
        for(const int &p:graph[i]){
            if (taken[p]) continue;
            if(find(visiting.begin(),visiting.end(),p)!=visiting.end()) return false;
            ans&=dfs(p);        
        }
        taken[i]=ans;
        visiting.erase(i);// omit or not, both OK
        return ans;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        graph.resize(numCourses);
        taken.resize(numCourses);
        for(const auto &p:prerequisites){
            int course=p[0];
            int pre=p[1];
            graph[course].push_back(pre);
        }

        for(int i=0;i<numCourses;i++) {
            if(!dfs(i)) return false;
        }

        return find(taken.begin(), taken.end(),false)==taken.end();
    }
};

/*

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

*/