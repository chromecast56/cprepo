/*
    Algorithm is as follows:

    1. BFS to find path from source to sink w/ minimum number of edges
    2. For each used edge, subtract the max flow that can be pushed in (min of the edges), and add the max flow to the return
    3. Repeat until no path from source to sink exists

    Time complexity is O(VE^2)

    (This algorithm is actually Edmond Karp, since it uses BFS to find MIN number of edges, instead of any path.
    Origonal time complexity is O(E|f|), where f is the max edge value.

    NOTICE: If edges aren't very big (assignment problem, etc) be sure to revert to DFS
*/
#include <bits/stdc++.h>

using namespace std;

#define SRC -2
//find max flow from s to t
vector<int> adj[1001]; //adj list
int W[1001][1001]; //pairwise weights
void reset()
{
    for(int i=0;i<=1000;i++) {
        for(int j=0;j<=1000;j++) W[i][j]=0;
        adj[i].clear();
    }
}
//bfs to see if extra flow from s to t can be pushed, record path
int bfs(int s,int t,vector<int> &par)
{
    fill(par.begin(),par.end(),-1); //unvisited is -1, src is -2
    par[s]=SRC;
    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty())
    {
        int cur=q.front().first;
        int flow=q.front().second;
        q.pop();

        for (int next: adj[cur])
            if (par[next]==-1 && W[cur][next] > 0) {
                int nflow = min(flow,W[cur][next]);
                q.push({next,nflow}), par[next] = cur;

                if (next==t)
                    return nflow;
            }
    }

    return 0;
}
int max_flow(int s,int t)
{
    vector<int> par(1000);
    int res = 0;
    while(int flow = bfs(s,t,par))
    {
        res += flow;
        int i = t;
        while(par[i] != SRC) {
            assert(W[par[i]][i] > 0);
            W[par[i]][i] -= flow;
            W[i][par[i]] += flow;
            i = par[i];
        }
    }
    return res;
}
int main()
{
    int T;cin>>T;
    while(T--)
    {
        int N,M; cin>>N>>M;
        while(M--) {
            int a,b,w;cin>>a>>b>>w;
            adj[a].push_back(b);//adj[b].push_back(a);
            W[a][b]=w;//W[b][a]=w;
        }
        cout << max_flow(1,N) << '\n';
    }

    return 0;
}