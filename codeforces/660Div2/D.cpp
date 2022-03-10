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

int n;
vi G[MX];
int cnt[MX]; //count unhappy
int h[MX]; //happy index
int sz[MX]; //count total
bool res = 1;
void clear() {
    res = 1;
    for (int i=1;i<=n;i++) cnt[i] = sz[i] = h[i] = 0, G[i].clear();
}
void dfs(int cur = 1, int par = -1, int depth = 1) {

    int bsum = 0;
    for (auto ne: G[cur])
        if (ne != par) {
            dfs(ne, cur, depth + 1);
            sz[cur] += sz[ne];
            bsum += cnt[ne];
        }

    int needed = (sz[cur] - h[cur])>>1; //exact number of unhappy needed
    if (needed < bsum) res = 0; //unhappy to give surpasses, is impossbie

    cnt[cur] = needed;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int m;cin>>n>>m;
        clear();
        for (int i=1;i<=n;i++) cin >> sz[i];
        for (int i=1;i<=n;i++) cin >> h[i];

        for (int i=0;i<n-1;i++) {
            int a,b;cin>>a>>b;
            G[a].pb(b);
            G[b].pb(a);
        }


        dfs();

        cout << (res? "YES\n":"NO\n");
    }

    return 0;
}