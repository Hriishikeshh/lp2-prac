    #include<bits/stdc++.h>
    using namespace std;

    struct Job{
        char id;
        int deadline;
        int profit;
    };

    bool cmp(Job a,Job b){
        return a.profit > b.profit;
    }

    void jobScheduling(vector<Job>& jobs){
        int n=jobs.size();
        vector<char>id(n,'-');
        vector<bool>slot(n,false);

        sort(jobs.begin(),jobs.end(),cmp);
        int profit=0;
        for(int i=0;i<n;i++){
            for(int j=min(n,jobs[i].deadline)-1;j>=0;j--){
                if(!slot[j]){
                    slot[j]=true;
                    id[j]=jobs[i].id;
                    profit+=jobs[i].profit;
                    break;
                }
            }
        }

        cout<<"job id's selected : ";
        for(int i=0;i<id.size();i++){
            if(id[i]!='-') cout<<id[i]<<" ";
        }
        cout<<"maximum profit : "<<profit;

    }


    void prims(vector<vector<pair<int,int>>>& adj){
        int n=adj.size();
        vector<int>vis(n,0);
        vector<int> parent(n,-1);
        vector<int>key(n,INT_MAX);

        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

        pq.push({0,0});
        int sum=0;

        while(!pq.empty()){
            pair<int,int> top=pq.top();
            pq.pop();

            int node=top.second;
            int wt=top.first;

            if(vis[node]) continue;

            // add to mst and mark visited
            sum+=wt;
            vis[node]=1;

            for(auto it:adj[node]){
                int n2=it.first;
                int wt2=it.second;
                if(!vis[n2]){
                    parent[n2]=node;
                    pq.push({wt2,n2});
                    key[n2]=wt2;
                }
            }
        }

        cout<<"edges in mst"<<endl;
        for(int i=0;i<parent.size();i++){
            cout<<parent[i]<<" -> "<<i<<" weight = "<<key[i]<<endl;
        }

        cout<<"MST sum is : "<<sum;

    }

    void dijkstra(vector<vector<pair<int,int>>>& adj,int source){
        int n=adj.size();
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        vector<int>parent(n,-1);
        vector<int> dist(n,INT_MAX);

        pq.push({0,source});
        dist[source]=0;

        while(!pq.empty()){
            int wt=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            
            for(auto it:adj[node]){
                int adjnode=it.first;
                int adjwt=it.second;
                if(adjwt+dist[node] < dist[adjnode]){
                    parent[adjnode]=node;
                    dist[adjnode]=adjwt+dist[node];
                    pq.push({dist[adjnode],adjnode});
                }
            }
        }
        cout << "\nShortest distances from source node " << source << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "Node " << i <<  " -> "<<parent[i]<<" Distance: " << dist[i] << "\n";
        }

        cout << "\n--- Dijkstra's Shortest Paths from source " << source << " ---\n";
    for (int i = 0; i < n; i++) {
        cout << "Distance to node " << i << " = " << dist[i] << "\n";
    }

        cout << "\nPaths:\n";
        for (int i = 0; i < n; i++) {
            if (i == source) continue;
            vector<int> path;
            for (int cur = i; cur != -1; cur = parent[cur]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());
            cout << "Path to " << i << ": ";
            for (int j = 0; j < path.size(); j++) {
                cout << path[j];
                if (j < path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }

    }


    int main(){
        int t,e;
        cout<<"enter number of vertices and edges : ";
        cin>>t>>e;

        vector<vector<pair<int,int>>> adj(t);
        // for(int i=0;i<e;i++){
        //     cout<<"enter start node, end node, weight :";
        //     int u,v,wt;
        //     cin>>u>>v>>wt;
        //     adj[u].push_back({v,wt});
        //     adj[v].push_back({u,wt});
        // }

    //     adj[0].push_back({1, 1});
    // adj[1].push_back({0, 1});

    // adj[1].push_back({3, 2});
    // adj[3].push_back({1, 2});

    // adj[3].push_back({4, 12});
    // adj[4].push_back({3, 12});

    // adj[4].push_back({2, 11});
    // adj[2].push_back({4, 11});

    // adj[2].push_back({3, 10});
    // adj[3].push_back({2, 10});

    // adj[0].push_back({2, 7});
    // adj[2].push_back({0, 7});

    // adj[2].push_back({5, 6});
    // adj[5].push_back({2, 6});

    // adj[0].push_back({5, 5});
    // adj[5].push_back({0, 5});

        // prims(adj);

        // dijkstra(adj,0);

        vector<Job> jobs = {
            {'a', 2, 100},
            {'b', 1, 19},
            {'c', 2, 27},
            {'d', 1, 25},
            {'e', 3, 15}
        };
    
        jobScheduling(jobs);

    }