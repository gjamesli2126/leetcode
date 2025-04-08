#include <bits/stdc++.h>
#define testMain main
using namespace std;

/*********************** Robot Interface *************************/
// This is the robot's control interface.
// You should not implement it, or speculate about its implementation.
class Robot {
public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    virtual bool move() = 0;

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    virtual void turnLeft() = 0;
    virtual void turnRight() = 0;

    // Clean the current cell.
    virtual void clean() = 0;
};
/*********************** End of Robot Interface *************************/


/*********************** Robot Simulation *************************/
// This is a simulated implementation of the Robot interface for testing purposes.
class RobotSim : public Robot {
private:
    vector<vector<int>> room;   // 1: accessible, 0: wall
    int rows, cols;
    int r, c;                   // current position of the robot
    int dir;                    // current direction: 0 = up, 1 = right, 2 = down, 3 = left
    // Direction vectors: up, right, down, left.
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};

public:
    // Set to store cleaned positions.
    set<pair<int,int>> cleaned;

    // Constructor: takes the room grid and the starting position (row, col).
    RobotSim(vector<vector<int>> roomGrid, int startRow, int startCol)
            : room(roomGrid), r(startRow), c(startCol), dir(0) {
        rows = room.size();
        cols = room[0].size();
    }

    bool move() override {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        // Check if next cell is within bounds and is accessible.
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && room[nr][nc] == 1) {
            r = nr;
            c = nc;
            return true;
        }
        return false;
    }

    void turnLeft() override {
        dir = (dir + 3) % 4;
    }

    void turnRight() override {
        dir = (dir + 1) % 4;
    }

    void clean() override {
        cleaned.insert({r, c});
    }

    // Get the current position (for internal testing if needed)
    pair<int,int> getPosition() {
        return {r, c};
    }
};
/*********************** End of Robot Simulation *************************/


/*********************** Solution Skeleton *************************/

class Solution {
private:
   vector<vector<bool>> visited;//(400,vector<int>(200));
   Robot* robot;

    const pair<int,int> dirs[4]={
            {-1,0}, {0,1}, {1,0}, {0,-1} //!!! the dir must match with the real-time direction!
    };
   void goBack(){
       robot->turnLeft();
       robot->turnLeft();
       robot->move();
       robot->turnLeft();
       robot->turnLeft();
   }
   //assume org point=(0,0)
   void backtrack(int r,int c,int dir){
        visited[r][c]=true;
        robot->clean();
        //4 dirs
        for(int i=0;i<4;i++){
            int newDir=(i+dir)%4;
            auto [dr,dc]= dirs[newDir];
            int newR=r+dr;
            int newC=c+dc;
            if(!visited[newR][newC] && robot->move()){
                backtrack(newR,newC,newDir);
                goBack();
            }
            robot->turnRight();
        }
   }
public:
    void cleanRoom(Robot& robot) {
        this->robot=&robot;
        visited.resize(402, vector<bool>(202));
        backtrack(100,200,0);//dir=0 means up
    }
};
/*********************** End of Solution Skeleton *************************/


/*********************** Helper Function *************************/
// Helper function to run a test case and print pass (green) or fail (red)
void runTest(int testNum, vector<vector<int>> room, int startRow, int startCol) {
    // Create a simulated robot with the given room and starting position.
    RobotSim robot(room, startRow, startCol);

    // Instantiate the solution and call cleanRoom.
    Solution sol;
    sol.cleanRoom(robot);

    // To verify, compute the expected number of cells that should be cleaned.
    // We'll do a flood-fill (DFS) from the starting position on the room grid.
    int rows = room.size(), cols = room[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int expectedCount = 0;
    function<void(int,int)> dfs = [&](int r, int c) {
        if(r < 0 || r >= rows || c < 0 || c >= cols) return;
        if(visited[r][c] || room[r][c] == 0) return;
        visited[r][c] = true;
        expectedCount++;
        dfs(r-1, c);
        dfs(r+1, c);
        dfs(r, c-1);
        dfs(r, c+1);
    };
    dfs(startRow, startCol);

    int cleanedCount = robot.cleaned.size();

    bool pass = (cleanedCount == expectedCount);
    if(pass) {
        cout << "\033[1;32mTest Case " << testNum << " Passed\033[0m" << endl;
    } else {
        cout << "\033[1;31mTest Case " << testNum << " Failed\033[0m" << endl;
        cout << "Expected cleaned cells count: " << expectedCount << ", Got: " << cleanedCount << endl;
    }
}

/*********************** Main Test *************************/
int testMain(){
    // Test Case 1:
    // Room grid:
    // 1 1 1 1 1 0 1 1
    // 1 1 1 1 1 0 1 1
    // 1 0 1 1 1 1 1 1
    // 0 0 0 1 0 0 0 0
    // 1 1 1 1 1 1 1 1
    // Starting position: (1, 3)
    vector<vector<int>> room1 = {
            {1,1,1,1,1,0,1,1},
            {1,1,1,1,1,0,1,1},
            {1,0,1,1,1,1,1,1},
            {0,0,0,1,0,0,0,0},
            {1,1,1,1,1,1,1,1}
    };
    runTest(1, room1, 1, 3);

    // Test Case 2:
    // Room grid:
    // 1
    // Starting position: (0, 0)
    vector<vector<int>> room2 = {
            {1}
    };
    runTest(2, room2, 0, 0);

    // Test Case 3:
    // Grid: 40 rows x 56 columns.
    // The grid is provided as a 2D array.
    // (Here I assume that the starting position is (0,14) because the first row
    // contains 0's until index 14 and then 1's. Adjust if necessary.)
    vector<vector<int>> room3 = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            // ... add the remaining 35 rows exactly as provided
            // For brevity, here are placeholder comments. You should paste the rest of the rows
            // exactly as given in your test case.
            // Row 5:
            { /* 56 integers for row 5 */ },
            // Row 6:
            { /* 56 integers for row 6 */ },
            // ...
            // Row 39:
            { /* 56 integers for row 39 */ }
    };
    runTest(3, room3, 0, 14);

    return 0;
}