/*
                Problem is basically same as Xenia and Tree, but now you have to remove nodes also.
                Answer? Make ans[] into a multiset array, so you can add/remove values from previously existing red nodes
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
#define first F
#define second S
typedef vector<int> vi;
const int MAXN = 100100;
const int LN = 17;

int n,q;
int depth[MAXN], size[MAXN]; set<int> adj[MAXN];
int par[MAXN]; //centroid decomp tree
int f[LN][MAXN]; //lca dp
multiset<int> ans[MAXN]; //answer dp - smallest dist to red node
/*Preproccessing*/
void dfsdepth(int cur, int prev, int _depth=0) { //proccess depth and size arrays
    depth[cur] = _depth;
    f[0][cur] = prev;
    for (auto ne: adj[cur]) if (ne!=prev)
            dfsdepth(ne,cur,_depth+1);
}
void preproccess()
{
    memset(f,-1,sizeof(f));
    dfsdepth(1,-1);
    for (int i=1;i<LN;i++) for (int j=1;j<=n;j++) if (f[i-1][j]!=-1) f[i][j] = f[i-1][f[i-1][j]];
}
int LCA(int u,int v) {
    if (depth[u]<depth[v]) swap(u,v);
    int dx = depth[u]-depth[v];
    for (int i=0;i<LN;i++) if (dx>>i&1) u=f[i][u];
    if (u==v) return u;
    for (int i=LN-1;i>=0;i--) if (f[i][u] != f[i][v])
            u = f[i][u], v = f[i][v];
    return f[0][u];
}
int dist(int u,int v) {
    return depth[u]+depth[v]-2*depth[LCA(u,v)];
}
/*decomposition*/
int nn; //track number of nodes in subtree
void dfssize(int cur,int prev) {
    size[cur] = 1;
    nn++;
    for (auto ne:adj[cur]) if (ne!=prev) {
            dfssize(ne,cur);
            size[cur] += size[ne];
        }
}
int centroid(int cur,int prev) { //calculate centroid
    for (auto ne:adj[cur])
        if (ne!=prev && size[ne] > nn/2) return centroid(ne,cur);
    return cur;                 //since all "edges" are 1, first time we go under nn/2 is answer
}
void decompose(int root, int prev) //prev represents previous centroid
{
    nn=0;
    dfssize(root,-1);
    int centr = centroid(root,-1);
    par[centr] = prev; //assign parent of centroid, is -1 if root
    for (auto ne: adj[centr]) {
        adj[ne].erase(centr);
        decompose(ne,centr);
    }
}
/*queries*/
void add(int u) //change u to red, update all ans values above u
{
    int x = u;
    while(x != -1) {
        ans[x].insert(dist(u,x));
        x = par[x];
    }
}
void remove(int u) //change u to blue, update all ans values above u
{
    int x = u;
    while(x != -1) {
        auto it = ans[x].find(dist(u,x));
        ans[x].erase(it); //default multiset erase erases multiple elements!!!!!!!!!
        x = par[x];
    }
}
int query(int u)
{
    int x = u;
    int res = 1e9;
    while(x != -1) {
        if (!ans[x].empty()) res = min(res,*ans[x].lower_bound(0)+dist(u,x));
        x = par[x];
    }
    return res==1e9? -1:res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin>>n;
    for (int i=0;i<n-1;i++) {
        int a,b; cin>>a>>b;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    preproccess();
    decompose(1,-1);
    cin>>q;
    while(q--) {
        int t,v;cin>>t>>v;
        if (t==0)
            if (ans[v].empty() || *ans[v].lower_bound(0) != 0)
                add(v);
            else remove(v);
        else cout<<query(v)<<'\n';
    }

    return 0;
}