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

int x,dia,d=0; //store farthest node from node 1, and current diameter, and distance
void dfs(int u,vector<vi> &adj, int par = -1,int depth=0) {
    if (dia < depth)
        dia = depth, x = u;
    for (auto v: adj[u])
        if (v != par)
            dfs(v,adj,u,depth+1);
}
void diameter(vector<vi> &adj) {
    x = 1,dia = 0;
    dfs(1,adj);
    dfs(x,adj);
}
void dist(int u,int v,vector<vi> &adj, int par = -1,int depth=0) {
    if (u==v) d = depth;
    for (auto ne: adj[u])
        if (ne != par)
            dist(ne,v,adj,u,depth+1);
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n,a,b,da,db;cin>>n>>a>>b>>da>>db;
        vector<vi> G(n+1);
        for (int i=0;i<n-1;i++) {
            int u,v;cin>>u>>v;
            G[u].pb(v);
            G[v].pb(u);
        }

        diameter(G);
        dist(a,b,G);

        if (d <= da)
            cout << "Alice\n";
        else if (da*2 >= dia)
            cout << "Alice\n";
        else if (db <= 2*da)
            cout << "Alice\n";
        else
            cout << "Bob\n";

        //cout << dia << ' ' << d  << '\n';
    }


    return 0;
}