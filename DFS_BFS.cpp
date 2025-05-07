#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Recursive DFS
void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

// Recursive BFS Helper
void bfs_recursive(queue<int>& q, const vector<vector<int>>& graph, vector<bool>& visited) {
    if (q.empty()) return;

    int node = q.front();
    q.pop();
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }

    bfs_recursive(q, graph, visited);
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    vector<vector<int>> graph(edges, vector<int>());    
    for (int i = 0; i < vertices; i++) {
        graph[i].clear();  // Initialize adjacency list
    }

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (e.g., 0 1):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // Undirected graph
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "\nDFS Traversal: ";
    vector<bool> visited_dfs(vertices, false);
    dfs(start, graph, visited_dfs);

    cout << "\nBFS Traversal: ";
    vector<bool> visited_bfs(vertices, false);
    visited_bfs[start] = true;
    queue<int> q;
    q.push(start);
    bfs_recursive(q, graph, visited_bfs);

    return 0;
}
