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
#define lb lower_bound
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
const int N = 200000,LN = 20;
vi G[N];
int n,m;
int push[N],pa[N][LN],depth[N];
int LCA(int u,int v)
{
    if (depth[u] < depth[v]) {int t=u;u=v;v=t;}
    int diff = depth[u] - depth[v];
    for (int i=0;i<ceil(log2(n));i++) if ((diff>>i)&1) u = pa[i][u];
    if (u==v) return u;
    for (int i=LN-1;i>=0;i--)
        if (pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}
void dfs(int cur,int prev = -1,int _depth=0)
{
    pa[0][cur] = prev;
    depth[cur] = _depth;
    for (auto i: G[cur])
        if (i != prev)
            dfs(i,cur,_depth+1);
}
void dfs2(int cur,int prev=-1) {
    for (auto i: G[cur])
        if (i != prev)
            push[i] += push[cur], dfs2(i,cur);
}
int main()
{
    //setIO("gathering");
    cin>>n>>m;
    for (int i=0;i<n-1;i++) {
        int a,b;cin>>a>>b;
        G[a].pb(b);
        G[b].pb(a);
    }
    for (int i=0;i<LN;i++) for (int j=0;j<N;j++) pa[i][j] = -1;
    dfs(1);
    for (int i=1;i<LN;i++)
        for (int j=0;j<N;j++)
            if (pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];

    for (int i=0;i<m;i++) {
        int a,b;cin>>a>>b;
        int lca = LCA(a,b);
        if (lca==a) { //case 1, then "loop over" to other side
            push[1]++;
            for (auto ne: G[a]) if (depth[ne] > depth[a])
                    push[ne]--;
        }
        else { //case 2, then update on subtree
            push[a]++;
        }
    }

    dfs2(1);
    for (int i=1;i<=n;i++) {
        cout << !push[i] << '\n';
    }

    return 0;
}
