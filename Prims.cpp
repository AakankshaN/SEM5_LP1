#include <iostream>
#include <vector>
// #include <limits.h>
#include <numeric> // for accumulate
using namespace std;

int findMinVertex(vector<int> &key, vector<bool> &mstSet, int n) {
    int minKey = INT_MAX;
    int minIndex;

    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < minKey) {  //  ***** && aahe not ||
            minKey = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void primMST(vector<vector<int>> &graph, int n) {
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> mstSet(n, false);

    key[0] = 0; // Start from vertex 0

    for (int count = 0; count < n - 1; count++) {
        int u = findMinVertex(key, mstSet, n);
        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Edge \tWeight\n";
    for (int i = 1; i < n; i++) //here 1 pasun start karayach aahe coz o cha parent -1 aahe
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;

    cout << "Minimum Spanning Tree weight: " << accumulate(key.begin(), key.end(), 0) << endl;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    primMST(graph, n);

    return 0;
}






