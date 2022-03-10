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
int n,q; const int N = 5050; ll offset = 2000000;
int a[N];
ll f[N][N]; //the answer for subarray i...j
//int cache[N][N]; //compute all triples with endpoints i, __, j
int mp[4000100]; //store freqlist
int main()
{
    setIO("threesum");
    cin>>n>>q;
    for (int i=0;i<n;i++) cin>>a[i];
    vi ops;
    for (int i=0;i<n;i++) {
        ops.clear();
        for (int j=i+1;j<n;j++)
            f[i][j] = mp[-a[i]-a[j] + offset], //cache = ... merge the cache and f arrays to save memory
            mp[a[j] + offset]++,
            ops.pb(a[j] + offset);
        for (auto val: ops)
            mp[val]--;
    }

    for (int l=0;l<n;l++)
        for (int i=0;i+l<n;i++) {
            int j = i+l;
            f[i][j] = f[i+1][j] + f[i][j-1] - f[i+1][j-1] + f[i][j];
        }

    while(q--) {
        int l,r;cin>>l>>r;
        cout << f[--l][--r] << '\n';
    }

    return 0;
}
