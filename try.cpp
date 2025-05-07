#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// Manhattan Distance heuristic
int calculateHeuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if the cell is valid
bool isSafe(int x, int y, int rows, int cols, vector<vector<int>>& matrix, vector<vector<bool>>& visited) {
    if(x < 0 || y < 0 || x >= rows || y >= cols) return false;  //greater than  equal to bothhhhhhh yaha galti karti hu
    if(matrix[x][y] == 1) return false; // obstacle
    if(visited[x][y]) return false; // already visited
    return true;
}

// Print the final path
void printPath(pair<int, int> goal, vector<vector<pair<int, int>>>& parent) {
    stack<pair<int, int>> path;
    pair<int, int> curr = goal;

    while (curr != make_pair(-1, -1)) {
        path.push(curr);
        curr = parent[curr.first][curr.second];
    }

    cout << "Path from start to goal:\n";
    while (!path.empty()) {
        cout << "(" << path.top().first << ", " << path.top().second << ") ";
        path.pop();
    }
    cout << endl;
}

// A* algorithm without using struct or class
void aStarSearch(vector<vector<int>>& matrix, pair<int, int> start, pair<int, int> goal) {
    int rows = matrix.size(), cols = matrix[0].size();
    
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    // Min-heap priority queue storing tuples: (fCost, gCost, x, y)
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;

    int sx = start.first, sy = start.second;
    int gx = goal.first, gy = goal.second;

    int h = calculateHeuristic(sx, sy, gx, gy);
    pq.push({h, 0, sx, sy});

    int dx[] = {-1, 1, 0, 0}; // left , right, up, down
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        auto [f, g, x, y] = pq.top(); 
        pq.pop();

        if (visited[x][y]) 
            continue;
        visited[x][y] = true;

        if (x == gx && y == gy) {
            printPath(goal, parent);
            return;
        }

        for (int i = 0; i < 4; i++) {//zero pasun start karayala visarate!!
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isSafe(nx, ny, rows, cols, matrix, visited)) {//condition  visarate 1!!!
               int newG = g + 1;
                int newH = calculateHeuristic(nx, ny, gx, gy);
                int newF = newG + newH;

                pq.push({newF, newG, nx, ny});
                parent[nx][ny] = {x, y};
            }
        }
    }

    cout << "No path found from start to goal.\n";
}

// Driver
int main() {
    // vector<vector<int>> matrix = {
    // //   0  1  2  3  4
    //     {0, 0, 0, 1, 0}, // 0
    //     {1, 1, 0, 1, 0}, // 1
    //     {0, 0, 0, 0, 0}, // 2
    //     {0, 1, 1, 1, 1}, // 3
    //     {0, 0, 0, 0, 0}  // 4
     
    // };

    // // Starting point (row, col)
    // pair<int, int> start = {0, 0};

    // // Goal point (row, col)
    // pair<int, int> goal = {4, 4};
    // vector<vector<int>> mat = {
    //     {1,1,0,0},
    //     {1,1,1,0},
    //     {1,0,1,0},
    //     {1,1,1,0}
    // };

    // pair<int , int> start = {0,0};
    // pair<int , int> end   = {2,2};

    vector<vector<int>> mat {
        {0,1,0,1,0},
        {0,0,0,1,0},
        {0,0,0,1,0},
        {1,0,1,0,1},
        {1,0,0,1,1}
    };

    pair<int,int> start = {0,0};
    pair<int,int> end = {4,2};

    aStarSearch(mat, start, end);

    return 0;
}
 