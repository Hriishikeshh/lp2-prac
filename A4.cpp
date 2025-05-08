#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>>& Graph, int c, int k, vector<int>& output)
{
    for(int i = 0; i < Graph.size(); i++)
    {
        if(Graph[k][i] == 1 && output[k] == c)
        {
            return false;
        }
    }
    return true;
}

bool graphColoring(vector<vector<int>>& Graph, int k, int n, int m, vector<int>& output)
{
    if(k == n)
    {
        return true;
    }
    for(int i = 0; i < m; i++)
    {
        output[k] = i;
        if(graphColoring(Graph, k+1, n, m, output))
        {
            return true;
        }
        output[k] = -1;
    }
    return false;
}

bool graphColorBranchBound(vector<vector<int>>& Graph, int k, vector<int>& output, int n, int m, vector<unordered_set<int>>& availableColors) {
    if (k == n) 
        return true;

    for (int c : availableColors[k]) {
        if (isSafe(Graph, k, c, output)) {
            output[k] = c;

            vector<unordered_set<int>> tempColors = availableColors;
            for (int j = 0; j < n; j++) {
                if (Graph[k][j] == 1) {
                    tempColors[j].erase(c);
                }
            }

            if (graphColorBranchBound(Graph, k + 1, output, n, m, tempColors))
                return true;

            output[k] = -1;
        }
    }
    return false;
}

int main() {
    cout << "Enter the number of vertices in the graph: ";
    int n;
    cin >> n;

    vector<vector<int>> G(n, vector<int>(n, 0));

    cout << "Enter the number of edges: ";
    int e;
    cin >> e;

    cout << "Enter source and destination pairs (0-based index): " << endl;
    for (int i = 0; i < e; i++) {
        int src, dest;
        cin >> src >> dest;

        if (src >= 0 && src < n && dest >= 0 && dest < n) {
            G[src][dest] = 1;
            G[dest][src] = 1;
        } else {
            cout << "Invalid edge! Enter values between 0 and " << n - 1 << endl;
            i--; 
        }
    }

    int m;
    cout << "Enter the number of colors: ";
    cin >> m;

    vector<int> arr(n, -1);
    cout << "\nSolving using Backtracking...\n";
    if (graphColoring(G, 0, n, m, arr)) {
        cout << "Graph colored successfully with " << m << " colors (Backtracking):\n";
        for (int i = 0; i < n; i++) {
            cout << "Vertex " << i << " -> Color " << arr[i] + 1 << endl;
        }
    } else {
        cout << "Graph cannot be colored with " << m << " colors using Backtracking." << endl;
    }
    // fill(arr.begin(), arr.end(), -1);

    // vector<unordered_set<int>> availableColors(n);
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         availableColors[i].insert(j);
    //     }
    // }

    // cout << "\nSolving using Branch and Bound...\n";
    // if (graphColorBranchBound(G, 0, arr, n, m, availableColors)) {
    //     cout << "Graph colored successfully with " << m << " colors (Branch and Bound):\n";
    //     for (int i = 0; i < n; i++) {
    //         cout << "Vertex " << i << " -> Color " << arr[i] + 1 << endl;
    //     }
    // } else {
    //     cout << "Graph cannot be colored with " << m << " colors using Branch and Bound." << endl;
    // }

    return 0;
}