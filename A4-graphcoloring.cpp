#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>>& graph, int v, vector<int>& color, int c)
{
    for(int i = 0; i < graph.size(); i++)
    {
        if(graph[v][i] && color[i] == c)
        {
            return false;
        }
        return true;
    }
}

bool solveUsingBacktracking(vector<vector<int>>& graph, int v, vector<int>&color, int m)
{
    if(v == graph.size())
    return true;

    for(int i = 1; i <= m; i++)
    {
        if(isSafe(graph, v, color, i))
        {
            color[v] = i;
            if(solveUsingBacktracking(graph, v+1, color, m))
            {

                return true;
            }
            color[v] = 0;
        }
    }
    return false;
}

int selectMRV(vector<int>& color, vector<unordered_set<int>>& domain)
{
    int minSize = INT_MAX;
    int selected = -1;
    for(int i = 0; i < color.size(); i++)
    {
        if(color[i] == 0 && domain[i].size() < minSize)
        {
            minSize = domain[i].size();
            selected = i;
        }
    }
    return selected;
}
bool solveUsingBranchAndBound(vector<vector<int>>& graph, vector<int>& color, vector<unordered_set<int>>& domain, int maxColor)
{
    bool complete = true;
    for(int c: color)
    {
        if(c == 0)
        {
            complete = false;
            break;
        }
    }
    if(complete) return true;
    int v = selectMRV(color, domain);
    if(v == -1 || domain.empty()) return false;
    for(int c: domain[v])
    {
        if(isSafe(graph, v, color, c))
        {
            color[v] = c;
            vector<unordered_set<int>> tempdomain = domain;
            for(int i = 0; i < graph.size(); i++)
            {
                if(graph[v][i])
                {
                    domain[i].erase(c);
                }
            }

            if(solveUsingBranchAndBound(graph, color, tempdomain, maxColor))
            {
                return true;
            }
            color[v] = 0;
        }
    }
    return false;
}

int main()
{
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Enter edges (0-based index):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }
    int m;
    cout << "Enter maximum number of colors: ";
    cin >> m;
    
    vector<int> color(n, 0);

    cout<<"Solve using backtracking...\n";
    if(solveUsingBacktracking(graph, 0, color, m))
    {
        cout<<"Solution found using backtracking:\n";
        for(int i =0; i< n; i++)
        {
            cout<<"Vertex "<<i<<" ->Color "<<color[i]<<"\n";
        }
    }
    else
    {
        cout << "No solution found using Backtracking.\n";
    }

    fill(color.begin(), color.end(), 0);
    vector<unordered_set<int>> domain(n);
    for(int i = 0; i < n; i++)
    {
        for(int c = 1; c <= m; c++)
        {
            domain[i].insert(c);
        }
    }

    cout<<"Solving using branch and bound....\n";
    if(solveUsingBranchAndBound(graph, color, domain, m))
    {
        cout<<"Solution found using branch and bound:\n";
        for (int i = 0; i < n; i++)
        cout << "Vertex " << i << " -> Color " << color[i] << "\n";
    }
    else {
        cout << "No solution found using Branch and Bound.\n";
    }
    return 0;
}