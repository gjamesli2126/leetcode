class Solution {
private:
    int r_max,c_max;
    void pathFinder(vector<vector<int>>& rooms, deque<pair<int,int>>& q){
        vector<vector<bool>> visited(r_max,vector<bool>(c_max,false));
        while(!q.empty()){
            auto [r0,c0]=q.front();
            q.pop_front();
            visited[r0][c0]=true;
            static const vector<pair<int,int>> dirs{
                {1,0},{0,1},{-1,0},{0,-1}
            };
            for(const auto& [dr,dc]:dirs){
                int r=r0+dr;
                int c=c0+dc;
                if(r<0 || r>=r_max || c<0 || c>=c_max || visited[r][c] || rooms[r][c]!=INT_MAX) continue;
                q.emplace_back(r,c);
                rooms[r][c]=1+rooms[r0][c0];
            }
        }


    }
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        r_max=rooms.size();
        c_max=rooms[0].size();
        deque<pair<int,int>> gates;
        for(int r=0;r<r_max;r++){
            for(int c=0;c<c_max;c++){
                if(rooms[r][c]==0) gates.emplace_back(r,c);
            }
        }
        pathFinder(rooms,gates);
    }
};