#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}
/*

Gameplan, utilize small to large merging. Start from the leafs of the tree and work up. When you get to a node i
, use the dsu to find the set of values it links to - this set is gaurenteed to include all of the values
in the i's subtree - use lower_bound or binary search to find its index and find # of values greater than it.

Similar to inversion counting in an array, except generalized to a tree

 */
int n;
int p[100100],d[100100], val[100100];
set<int> s[100100];
vi G[100100];
int res[100100];
struct DSU { //regular dsu, except we also store the "values" of each indicie using small to large merging! :)

    vi p,sz;
    vector<Tree<int>> s;
    DSU(int n,int *val) {
        p.resize(n),sz.resize(n);s.resize(n);
        for (int i=0;i<n;i++)
            p[i]=i,sz[i]=1,s[i].insert(val[i]);
    }
    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }
    void merge(int u,int v) {
        u = find(u), v = find(v);
        if (u!=v) {
            if (sz[u]<sz[v]) swap(u,v);
            p[v]=u;
            for (auto va: s[v])
                s[u].insert(va);
            sz[u]+=sz[v];
        }
    }
    int count(int u) {
        return sz(s[find(u)]) - 1 - s[find(u)].order_of_key(val[u]);
    }
};

vpii rbfs;
void dfs(int cur,int par = -1,int depth=0) {
    rbfs.pb({depth,cur}); d[cur] = depth;
    for (auto ne: G[cur])
        if (ne != par)
            dfs(ne,cur,depth+1);
}
int main()
{
    ofstream fout("promote.out");
    ifstream fin("promote.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n;
    for (int i=0;i<n;i++) fin>>val[i];
    for (int i=1;i<n;i++) {
        fin>>p[i]; p[i]--;
        G[i].pb(p[i]);
        G[p[i]].pb(i);
    }

    dfs(0);
    sort(rall(rbfs));
    DSU dsu(n,val);

    for (auto node: rbfs) {
        int i = node.S;
        for (auto sub: G[i])
            if (d[sub]>d[i])
                dsu.merge(sub,i);
        res[i] = dsu.count(i);
    }

    for (int i=0;i<n;i++)
        fout << res[i] << '\n';

    return 0;
}