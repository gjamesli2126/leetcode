class Solution {
public:
    unordered_map<string,vector<string>> graph;
    void dfs()
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        //graph
        for(const vector<string>& p:tickets){
            string src=p[0];
            string tar=p[1];
            graph[src].push_back(tar);
        }
        //topological sort

    }
};