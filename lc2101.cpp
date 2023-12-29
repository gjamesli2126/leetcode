class Solution {
public:
    int maxExp = 1;
    vector<vector<int>> graph;
    vector<bool> visited;

    bool affect(const vector<int>& src, const vector<int>& tar){
        return pow(src[0]-tar[0],2) + pow(src[1]-tar[1],2) <= pow(src[2],2);
    }

    void dfs(int bombId, const int &n, int &count) {
        if (visited[bombId]) return;
        visited[bombId] = true;
        count++;
        for (const int &bomb2 : graph[bombId]) {
            dfs(bomb2, n, count);
        }
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        if (n == 1) return 1;
        graph.resize(n);
        visited.resize(n, false);

        // build graph
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(i==j) continue;
                if (affect(bombs[i], bombs[j])) {
                    graph[i].push_back(j);
                }
            }
        }

        // find max
        for (int i = 0; i < n; i++) {
            fill(visited.begin(), visited.end(), false);
            int count = 0;
            dfs(i, n, count);
            maxExp = max(maxExp, count);
        }
        return maxExp;
    }
};
