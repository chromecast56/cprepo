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
}
int n,k;

int a[60000];
int g[60][60];
vi G[60000];
int d[60000];

int vis[60000];
int dijkstra(int s) {
    for (int i=1;i<=n;i++) d[i] = 1000000;
    d[s] = 0;
    set<pii> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->S;
        q.erase(q.begin());

        for (auto e :G[v]) {
            int to = e;
            int len = abs(to-v);

            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                q.insert({d[to], to});
            }
        }
    }
    return d[n-1];
}
int main()
{
    setIO();
    cin>>n>>k;

    for (int i=0;i<n;i++) cin>>a[i];
    for (int i=0;i<k;i++) {
        string x;cin>>x;
        for (int j=0;j<sz(x);j++)
            g[i][j] = x[j]-'0';
    }

    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (i!=j && g[a[i]-1][a[j]-1])
                G[i].pb(j);

    cout << dijkstra(0) << '\n';

    return 0;
}


