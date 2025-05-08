#include <bits/stdc++.h>
#include<iostream>
using namespace std;

void bfsutil(vector<vector<int>>& adj,queue<pair<int,int>>& q,vector<bool>& vis){
    if(q.empty()) return;

    pair<int,int> top=q.front();
    q.pop();
    int node=top.first;
    int level=top.second;

    cout<<"node - "<<node<<" level - "<<level<<endl;
    for(auto it:adj[node]){
        if(!vis[it]){
            vis[it]=true;
            q.push({it,level+1});
        }
    }

    bfsutil(adj,q,vis);
}

void bfsrecursive(vector<vector<int>>& adj){
    int n=adj.size();
    vector<bool> vis(n,false);

    for(int i=0;i<n;i++){
        if(!vis[i]){
            queue<pair<int,int>> q;
            q.push({i,0});
            vis[i]=true;
            
            cout<<"node starting from "<<i;
            bfsutil(adj,q,vis);
        }
    }
}

void dfsutil(int node,int level,vector<vector<int>>& adj,vector<bool>& vis){
    vis[node]=1;
    cout<<"Node - "<<node<<" level - "<<level<<endl;
    for(auto it:adj[node]){
        if(!vis[it]){
            dfsutil(it,level+1,adj,vis);
        }
    }
}

void dfsrecursive(vector<vector<int>> &adj){
    int n=adj.size();
    vector<bool>vis(n,false);

    for(int i=0;i<n;i++){
        if(!vis[i]){
            cout<<"dfs traversal from "<<i<<endl;
            dfsutil(i,0,adj,vis);
        }
    }
}


int main(){
    int v,e;
    cout<<"enter vertices : ";
    cin>>v;
    cout<<"enter edges : ";
    cin>>e;

    vector<vector<int>> adj(v);
    for(int i=0;i<e;i++){
        int u,v;
        cout<<"enter vertices with edge (u v): ";
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // for(int i=0;i<n)

    // bfsrecursive(adj);
    dfsrecursive(adj);
}