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
const ll MOD = 1e9+7; //998244353
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
int n,m,k;
vl s[5500];
ll vec[5500];
ll let[300];
ll f[5500], dp[5500]; //f is result, dp is secondary
ll xpow(ll a,ll b) {
    if (a==0||a==1) return a;

    if (b==0) return 1;
    if (b==1) return a;
    ll x = xpow(a,b>>1);
    x = (x*x)%MOD;
    if (b&1) return (x*a)%MOD;
    return x;
}
void do_dp() {
    dp[0] = 1;
    for (int i=1;i<=k;i++) //knapsack count for all
        for (int j=0;j<n;j++)
            if (i >= vec[j])
                dp[i] = (dp[i] + dp[i-vec[j]])%MOD;

    for (int i=1;i<=n;i++) //count for ending in a certain stack (...)+word
        for (int j=0;j<sz(s[i]);j++)
            f[i] = (f[i] + dp[k-s[i][j]])%MOD;
}
int main()
{
    setIO("poetry");
    cin>>n>>m>>k;
    for (int i=0;i<n;i++) {
        int a,b;cin>>a>>b;
        s[b].pb(a);
        vec[i] = a;
    }

    do_dp(); //for each "rhyme stack", calculate number possibilities ending w word from respective stack

    for (int i=0;i<m;i++) {
         char c; cin >> c;
         let[c]++;
    }
    ll res = 1;
    for (int i='A';i<='Z';i++) //sort the letters, for a "letter group", the answer is f[i]^sz sum over all i
        if (let[i]) {
            ll sum = 0;
            for (int j=1;j<=n;j++)
                if (f[j])
                    sum = (sum+xpow(f[j],let[i]))%MOD;
            res = (res*sum)%MOD;
        }

    cout << res << '\n';

    return 0;
}
