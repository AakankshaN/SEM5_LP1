#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int find(int v, vector<int> &parent) {
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent[v], parent); // Path compression
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    int uRoot = find(u, parent);
    int vRoot = find(v, parent);

    if (uRoot != vRoot) {
        if (rank[uRoot] < rank[vRoot])
            parent[uRoot] = vRoot;
        else if (rank[uRoot] > rank[vRoot])
            parent[vRoot] = uRoot;
        else {
            parent[vRoot] = uRoot;
            rank[uRoot]++;
        }
    }
}

void kruskalMST(vector<Edge> &edges, int n) {
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    vector<Edge> result;
    for (Edge e : edges) {
        if (find(e.u, parent) != find(e.v, parent)) {
            result.push_back(e);
            unionSet(e.u, e.v, parent, rank);
        }
    }

    cout << "Edge \tWeight\n";
    for (Edge e : result)
        cout << e.u << " - " << e.v << "\t" << e.weight << "\n";
}

int main() {
    // int n, m;
    // cout << "Enter number of vertices and edges: ";
    // cin >> n >> m;

    // vector<Edge> edges(m);
    // cout << "Enter edges (u v weight):\n";
    // for (int i = 0; i < m; i++)
    // {
    //     cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    //     // cout << "Read edge: " << edges[i].u << " " << edges[i].v << " " << edges[i].weight << endl;
    //     // Uncomment the above line to debug edge reading
    // }

    int n = 4; // Number of vertices
    int m = 5; // Number of edges

    vector<Edge> edges = {
        {0, 1, 5},
        {0, 2, 3},
        {1, 2, 2},
        {1, 3, 1},
        {2, 3, 4}
    };

    // Just to confirm the input is loaded correctly
    cout << "Edges (u v weight):\n";
    for (int i = 0; i < m; i++) {
        cout << edges[i].u << " " << edges[i].v << " " << edges[i].weight << endl;
    }

    kruskalMST(edges, n);

    return 0;
}
