/*
                            Algo: Hard to do stuff on regular graph, we first compress it using Tarjan SCC,
                            and then assign node values according to their 'subtree' sizes. Then, run dijskra
                            and reverse dijskra, and loop over all nodes for max val of:
                                dist(src,i) + rev_dist(j,src)

                            Where i and j are neighbors (and j connects to i)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxn = 100100;
const int NINF = -1e9;

int n,m;
vi adj[maxn];
vi G[maxn], GR[maxn]; //compressed graphs
int D[2][maxn]; //Dist array for dijskra/reverse dijskra

vi s; //stack
int t = 0, book_keeping = 0; //time, bookkeeping for ids
bool v[maxn]; //v array for Tarjan and Dijskra
int low[maxn], disc[maxn], sz[maxn]; //lowest disc reachable, discovery time, sz of scc
int id[maxn]; //ids for scc

void TarjanSCC(int ind)                     //learn it later
{
    low[ind] = disc[ind] = ++t;
    s.push_back(ind);
    v[ind] = 1;
    for (auto &ne: adj[ind]) {
        if (disc[ne] == -1) {
            TarjanSCC(ne);
            low[ind] = min(low[ind],low[ne]);
        }

        if (v[ne]) //analagous to "on stack"
            low[ind] = min(low[ind],disc[ne]);
    }

    if (low[ind] == disc[ind]) { //on backtrack is a scc root
        ++book_keeping;
        while(1) {
            int ne = s.back(); s.pop_back();
            v[ne] = 0;
            id[ne] = book_keeping; //mark for bookkeeping
            if (ind == ne) break;
        }
    }
}
void compress_graph() //compress graph using Tarjan, assign vals
{
    memset(disc,-1,sizeof(disc));
    for (int i=1;i<=n;i++)
        if (disc[i] == -1)
            TarjanSCC(i);

    for (int i=1;i<=n;i++) //update sizes
        sz[id[i]]++;

    for (int i=1;i<=n;i++) //add new vals into G
        for (auto &j: adj[i])
            if (id[i] != id[j]) //don't want self edge
                G[id[i]].push_back(id[j]);

    for (int i=1;i<=n;i++) //compress G
        if (!G[i].empty()) {
            sort(G[i].begin(),G[i].end());
            G[i].erase(unique(G[i].begin(),G[i].end()),G[i].end());

            for (auto &j: G[i])      //add vals to GR
                GR[j].push_back(i);
        }
}
void topSort(vi *g,int ind) {
    v[ind] = 1;
    for (auto &ne: g[ind])
        if (!v[ne])
            topSort(g,ne);
    s.push_back(ind);
}
void paths(vi *g,int src,bool b) //find longest paths (excluding value of src)
{
    s.clear();
    memset(v,0,sizeof(v));
    fill(D[b],D[b]+n+1, NINF);
    D[b][src] = 0;
    for (int i=1;i<=n;i++)          //find a topological sorting
        if (!v[i] && sz[i])
            topSort(g,i);

    while(!s.empty()) {
        int u = s.back(); s.pop_back();         //dp to find longest path
        if (D[b][u] != NINF)
            for (auto &ne: g[u])
                if (D[b][ne] < D[b][u]+sz[ne])
                    D[b][ne] = D[b][u]+sz[ne];
    }
}
int main()
{
    ofstream fout("grass.out");
    ifstream fin("grass.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    fin>>n>>m;
    for (int i=0;i<m;i++) {
        int a,b;
        fin>>a>>b;
        adj[a].push_back(b);
    }

    compress_graph();
    paths(G,id[1],0);
    paths(GR,id[1],1);
    int res = 0;
    for (int i=1;i<=n;i++) {
        if (!sz[i]) continue;
        for (auto &j: GR[i])
            res = max(res, D[0][i] + D[1][j] + sz[id[1]]); //(1,i] + (1,j] + [1]
    }
    fout << res << '\n';

    return 0;
}