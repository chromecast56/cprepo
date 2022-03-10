#include <bits/stdc++.h>

using namespace std;

int N,Q;

//DSU code without path compression
struct DSU
{
    int par[100001];
    int sz[100001];
    int size(int x) {
        return sz[find(x)];
    }
    int find(int x) {
        return par[x] == x ? x : (par[x] = find(par[x]));
    }
    void merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        sz[fy] += sz[fx];
        par[fx] = fy;
    }
};
struct query
{
    int k,v,i;
};
struct edge
{
    int a,b,w;
};
bool compQ(query a,query b)
{
    return a.k > b.k;
}
bool compE(edge a,edge b)
{
    return a.w > b.w;
}
edge e[100000];
query q[100001];
int res[100000];
int main()
{
    ofstream fout("mootube.out");
    ifstream fin("mootube.in");

    fin >> N >> Q;
    for (int i=0;i<N-1;i++)
    {
        int a,b,w; fin >> a >> b >> w;
        e[i] = {a,b,w};
    }
    for (int i=0;i<Q;i++)
    {
        int k,v; fin >> k >> v;
        q[i] = {k,v,i};
    }
    sort(q,q+Q,compQ); //decreasing k
    sort(e,e+N-1,compE); //decreasing w

    DSU dsu;
    for (int i=0;i<=100000;i++) //initialize DSU
        dsu.sz[i] = 1, dsu.par[i] = i;

    //Loop through every query, then merge all edges with weights higher than k
    //Then, see how many nodes are connected to the starting node
    //This will bypass the min edge weight connection rule
    int itr = 0;
    for (int i=0;i<Q;i++)
    {
        while(itr < N-1 && e[itr].w >= q[i].k)
            dsu.merge(e[itr].a,e[itr].b), itr++;
        res[q[i].i] = dsu.size(q[i].v)-1;
    }
    for (int i=0;i<Q;i++)
        fout << res[i] << "\n";

    return 0;
}