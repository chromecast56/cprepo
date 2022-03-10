/*
    What Dinc's algorithm does:

        - Create a 'level' graph, where each node is assigned to a level which says how far away it is from the src (BFS)
            Note that this graph will change over time bc some edges will be filled
            Also note that the level graph is a DAG
        - Now do DFS on the resulting graph, st at each node we must go to a higher level
            Using one DFS we can accumulate many augumenting paths and update/sum them up

        - Repeat the above steps until the level graph cannot reach the sink node, which means that we have
        successfully filled the graph and found the max flow

        Outer loop will run V times, BFS is O(E), and DFS is applied V times for O(VE)
        Time complexity is O(V^2E)

        Optimization:
            - Apply the inner loop for certain limits, starting from 2^30 and working your way down in powers of 2
            - Apply BFS for level graph (take into account limit) (E), then apply DFS until no flow is above the limit (VE)

        Optimized time complexity is O(VElog|f|) where f is the maximum edge weight

        This even makes it a viable alternative for the Assignment problem
 */
#include <bits/stdc++.h>

using namespace std;

struct edge {
    int a,b,f,c;
    //start, end, flow, capacity
};

#define inf 1e9
#define MAXN 1000
vector<edge> e;
vector<int> g[MAXN];
int pt[MAXN];
int d[MAXN];
queue<int> q;

int s,t; //source, sink
void add_edge(int a, int b, int c) {
    edge ed = {a,b,0,c};
    g[a].push_back(e.size()); //forward edges
    e.push_back(ed);

    ed = {b,a,c,c};
    g[b].push_back(e.size()); //backward edges
    e.push_back(ed);
} //note, to get opposite edge you do ind^1

bool bfs(int lim) { //create level graph
    for (int i = s; i <= t; i++)
        d[i] = inf;
    d[s]=0;
    q.push(s);

    while (!q.empty() && d[t] == inf) {
        int cur = q.front(); q.pop();
        for (int i = 0; i < g[cur].size(); i++) {
            int id = g[cur][i];
            int to = e[id].b;

            if (d[to] == inf && e[id].c-e[id].f >= lim) {
                d[to] = d[cur]+1;
                q.push(to);
            }
        }
    }
    while (!q.empty()) q.pop();

    return d[t] != inf;
}

bool dfs(int v, int flow) { //dfs for augumenting paths, return true if a path is found
    if (flow == 0) return 0;
    if (v == t)
        return 1;

    for (; pt[v] < g[v].size(); pt[v]++) {
        int id = g[v][pt[v]];
        int to = e[id].b;

        if (d[to] == d[v]+1 && e[id].c-e[id].f >= flow) { //if 'to' is in next level and edge has enough capacity
            int pushed = dfs(to, flow); //if a path is found
            if (pushed) {
                e[id].f += flow;
                e[id ^ 1].f -= flow;
                return 1;
            }
        }
    }
    return 0;
}
int max_flow() {
    int res = 0;
    for (int lim = (1<<30);lim >= 1;) {
        if (!bfs(lim)) {
            lim >>= 1;
            continue;
        }

        for (int i = s; i <= t; i++)
            pt[i] = 0;

        while (dfs(s,lim))
            res+=lim;
    }
    return res;
}

int main()
{
    int N,M; cin>>N>>M;

    s = 1, t = N;
    while(M--) {
        int a,b,w;
        cin>>a>>b>>w;

        add_edge(a,b,w);
    }

    cout << max_flow() << '\n';

    return 0;
}