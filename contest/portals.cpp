#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
#define all(x) (x).begin(),(x).end()
#define pb push_back

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
}
int n;
struct portal {
    int a,b,c,d;
};
struct edge {
    int u,v,w;
    bool operator<(edge const& a) {
        return w < a.w;
    }
};
vi cost;
vi G[200100];
int v[200100];
vector<portal> p;
void search(int cur,int col) {
    v[cur] = col;
    for (auto ne: G[cur])
        if (!v[ne])
            search(ne,col);
}
vector<edge> edges;
struct DSU{
    int par[200100];
    int sz[200100];
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
int main()
{
    setIO();
    cin>>n;
    for (int i=0;i<n;i++) {
        int co,a,b,c,d;cin>>co>>a>>b>>c>>d;
        cost.pb(co);
        G[a].pb(b), G[b].pb(a), G[c].pb(d), G[d].pb(c);
        p.pb({a,b,c,d});
    }

    int color = 0;
    for (int i=1;i<=2*n;i++)
        if (!v[i]) {
            search(i,++color);
        }

    for (int i=0;i<n;i++)
        if (v[p[i].a] == v[p[i].b] && v[p[i].c] == v[p[i].d])
            edges.pb({v[p[i].a],v[p[i].c],cost[i]});

    sort(all(edges));
    ll res = 0;
    DSU dsu;
    for (int i=0;i<100100;i++) dsu.par[i] = i, dsu.sz[i] = 1;
    for (auto e: edges)
        if (dsu.find(e.u) != dsu.find(e.v))
            res += e.w, dsu.merge(e.u,e.v);

    cout << res << '\n';

    return 0;
}


