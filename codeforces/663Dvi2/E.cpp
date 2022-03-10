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
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

vi G[3*MX];
vi d[3*MX]; //store verticies at each depth
vi path; //store the path
int v[3*MX];
int n,m;
void clear() {
    path.clear();
    for (int i=1;i<=n;i++)
        G[i].clear(), d[i].clear(), v[i] = 0;
}
void dfs(int cur = 1, int depth = 1) {
    v[cur] = 1;
    if (path.size() < (n-n/2))
        path.pb(cur);
    d[depth].pb(cur);

    for (auto ne: G[cur])
        if (!v[ne])
            dfs(ne,depth+1);

    if (path.size() < (n-n/2))
        path.pop_back();
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;cin>>t;
    while(t--) {
        cin>>n>>m;

        clear();
        for (int i=0;i<m;i++) {
            int a,b;cin>>a>>b;
            G[a].pb(b);
            G[b].pb(a);
        }

        dfs(1);

        if (!path.empty()) {
            cout << "PATH\n";
            cout << path.size() << '\n';
            for (auto ne: path)
                cout << ne << ' ';
            cout << endl;
        }
        else {
            cout << "PAIRING\n";
            vpii res;
            for (int i=1;i<=n;i++)
                while(d[i].size() >= 2) {
                    int a = d[i].back(); d[i].pop_back();
                    int b = d[i].back(); d[i].pop_back();
                    res.pb({a,b});
                }

            cout << res.size() << '\n';
            for (auto ne: res)
                cout << ne.F << ' ' << ne.S << '\n';
        }
    }

    return 0;
}