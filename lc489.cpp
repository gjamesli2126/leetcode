#include <bits/stdc++.h>
#define testMain main
using namespace std;

// Mock implementation of the Robot interface for testing.
class Robot {
public:
    Robot(const vector<vector<int>>& room, int row, int col)
            : room(room), x(row), y(col), dir(0) {
        m = room.size();
        n = room[0].size();
    }

    bool move() {
        static int dx[4] = {-1, 0, 1, 0};  // up, right, down, left
        static int dy[4] = {0, 1, 0, -1};
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx < 0 || nx >= m || ny < 0 || ny >= n || room[nx][ny] == 0)
            return false;
        x = nx;
        y = ny;
        return true;
    }

    void turnLeft() {
        dir = (dir + 3) % 4;
    }

    void turnRight() {
        dir = (dir + 1) % 4;
    }

    void clean() {
        cleaned.insert({x, y});
    }

    int getCleanedCount() const {
        return cleaned.size();
    }

private:
    vector<vector<int>> room;
    int x, y, dir;
    int m, n;
    set<pair<int,int>> cleaned;
};

// User's Solution stub.

class Solution{
private:

    void back1step(Robot& ro){
        ro.turnRight();
        ro.turnRight();
        ro.move();
        ro.turnRight();
        ro.turnRight();
    }
    unordered_set<string> visited;
    vector<int> dirs{1,0,-1,0,1};//turning Right
    inline string makehash(int r,int c) {
        return to_string(r)+'-'+ to_string(c);
    }
    void backtrackDFS(Robot& ro,int r,int c,int dir){
        visited.insert(makehash(r,c));//slow, use vector instead
        ro.clean();
        for(int i=0;i<4;i++){
            int newDir=(dir+i)%4;
            int dr=dirs[newDir];
            int dc=dirs[newDir+1];//turn right
            string hash= makehash(r+dr,c+dc);//slow
            if(!visited.contains(hash) && ro.move()){
                backtrackDFS(ro,r+dr,c+dc,newDir);
                back1step(ro);
            }
            ro.turnRight();
        }
    }
public:
    void cleanRoom(Robot& robot) {
        backtrackDFS(robot,0,0,0);//dir:0 1 2 3, turning right
    }
};

// Utility to count total accessible cells in the room.
int countAccessible(const vector<vector<int>>& room) {
    int cnt = 0;
    for (auto& row : room)
        for (int c : row)
            if (c == 1) cnt++;
    return cnt;
}

void runTest(int testNum,
             const vector<vector<int>>& room,
             int row, int col) {
    Robot robot(room, row, col);
    Solution sol;
    sol.cleanRoom(robot);

    int cleaned = robot.getCleanedCount();
    int total = countAccessible(room);
    if (cleaned == total) {
        cout << "Test Case " << testNum << " Passed: Robot cleaned all rooms." << endl;
    } else {
        cout << "Test Case " << testNum
             << " Failed: cleaned " << cleaned
             << " out of " << total << " accessible cells." << endl;
    }
}

int testMain() {
    // Example 1
    vector<vector<int>> room1 = {
            {1,1,1,1,1,0,1,1},
            {1,1,1,1,1,0,1,1},
            {1,0,1,1,1,1,1,1},
            {0,0,0,1,0,0,0,0},
            {1,1,1,1,1,1,1,1}
    };
    runTest(1, room1, 1, 3);

    // Example 2
    vector<vector<int>> room2 = {{1}};
    runTest(2, room2, 0, 0);

    return 0;
}
