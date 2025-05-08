#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Recursive BFS Helper
void bfsRecursiveUtil(queue<pair<int, int>>& q, vector<bool>& visited, const vector<vector<int>>& adj) {
    if (q.empty()) return;

    pair<int, int> front = q.front();
    q.pop();

    int node = front.first;
    int level = front.second;

    cout << "Node: " << node << " -- Level: " << level << "\n";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push(make_pair(neighbor, level + 1));
        }
    }

    bfsRecursiveUtil(q, visited, adj);
}

// Recursive BFS Disconnected Graph Handler
void bfsRecursive(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);

    cout << "\nRecursive BFS (Level-wise):\n";
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            queue<pair<int, int>> q;
            q.push(make_pair(i, 0));
            visited[i] = true;

            cout << "Starting BFS from node " << i << ":\n";
            bfsRecursiveUtil(q, visited, adj);
        }
    }
}

// Recursive DFS Helper
void dfsRecursiveUtil(int node, int level, vector<bool>& visited, const vector<vector<int>>& adj) {
    visited[node] = true;
    cout << "Node: " << node << " -- Level: " << level << "\n";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfsRecursiveUtil(neighbor, level + 1, visited, adj);
        }
    }
}

// Recursive DFS Disconnected Graph Handler
void dfsRecursive(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);

    cout << "\nRecursive DFS (Level-wise):\n";
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            cout << "Starting DFS from node " << i << ":\n";
            dfsRecursiveUtil(i, 0, visited, adj);
        }
    }
}

// Main
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    bfsRecursive(adj);
    dfsRecursive(adj);

    return 0;
}
