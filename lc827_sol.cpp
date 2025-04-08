#include <vector>
#include <unordered_set>
//#include <algorithm>
using namespace std;

class Solution {
private:
    // Direction vectors for exploring 4-neighbors (down, left, up, right)
    // The array is arranged so that for index i, the neighbor cell is (row + directions[i], col + directions[i+1])
    const int directions[5] = {1, 0, -1, 0, 1};
    int gridSize; // Dimension of the grid

    // Depth-First Search that marks an island with a unique island ID and computes its area.
    // It changes all connected 1's to islandId.
    int dfsMarkIsland(int row, int col, int islandId, vector<vector<int>>& grid) {
        grid[row][col] = islandId;   // Mark the cell with the island ID.
        int area = 1;                // Count the current cell.

        // Explore all 4 neighboring cells.
        for (int i = 0; i < 4; i++) {
            int newRow = row + directions[i];
            int newCol = col + directions[i + 1];
            // Check boundaries and see if the neighbor is part of an unvisited island (value 1).
            if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize && grid[newRow][newCol] == 1) {
                area += dfsMarkIsland(newRow, newCol, islandId, grid);
            }
        }
        return area;
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        gridSize = grid.size();
        vector<int> islandAreas;
        // islandAreas[i] will store the area of the island with id (i + 2).
        // We start island IDs from 2, because:
        //   0 -> water
        //   1 -> unvisited land
        int islandId = 2;

        // First pass: mark all islands with unique IDs and record their areas.
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (grid[row][col] == 1) {
                    int area = dfsMarkIsland(row, col, islandId, grid);
                    islandAreas.push_back(area);
                    islandId++;  // Prepare a new unique island ID for the next island.
                }
            }
        }

        // If there are no islands, flipping one water cell will create an island of area 1.
        if (islandAreas.empty()) {
            return 1;
        }

        int maxIslandArea = 0;
        // Second pass: For every water cell, consider flipping it to land.
        // Compute the potential island area by summing areas of all unique adjacent islands.
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (grid[row][col] == 0) { // Water cell found.
                    int combinedArea = 1; // Count the flipped cell.
                    unordered_set<int> seenIslandIds; // To avoid counting the same island more than once.

                    // Explore the 4 neighbors.
                    for (int i = 0; i < 4; i++) {
                        int newRow = row + directions[i];
                        int newCol = col + directions[i + 1];
                        if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize) {
                            int neighborIslandId = grid[newRow][newCol];
                            // If neighbor belongs to an island (id > 1) and hasn't been counted yet.
                            if (neighborIslandId > 1 && seenIslandIds.find(neighborIslandId) == seenIslandIds.end()) {
                                seenIslandIds.insert(neighborIslandId);
                                // Adjust the index: island id starts at 2, so islandAreas index = (neighborIslandId - 2)
                                combinedArea += islandAreas[neighborIslandId - 2];
                            }
                        }
                    }
                    maxIslandArea = max(maxIslandArea, combinedArea);
                }
            }
        }

        // If maxIslandArea is still 0, then the grid has no water (i.e. it's full of land),
        // so the island covers the whole grid.
        return maxIslandArea == 0 ? gridSize * gridSize : maxIslandArea;
    }
};