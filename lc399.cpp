class Solution {
private:
    unordered_map<string,unordered_map<string,double>> dict;
    
public:
    double bfs(const string& st0,const string& dst){
        if(st0==dst) return 1;
        unordered_map<string,double> visited;
        deque<string> dq{st0};
        visited[st0]=1;
        while(!dq.empty()){
            string st=dq.front();
            dq.pop_front(); 
            
            for(const auto &[forward,weight]:dict[st]){
                if(visited.find(forward)!=visited.end()) continue;
                visited[forward]=weight*visited[st];
                if(forward==dst) return visited[dst];
                dq.push_back(forward);
            }
        }
        return -1;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        const int N=values.size();

        //build damm graph
        for(int i=0;i<N;i++){
            dict[equations[i][0]][equations[i][1]]=values[i];
            dict[equations[i][1]][equations[i][0]]=1/values[i];
        }
        //traverse queres times
        vector<double> ansS;
        for(const auto &vec:queries){
            string st=vec[0],dst=vec[1];
            if(dict.find(st)==dict.end() || dict.find(dst)==dict.end()) ansS.push_back(-1.0);
            else ansS.push_back(bfs(st,dst));
            
        }
        return ansS;
    }
};