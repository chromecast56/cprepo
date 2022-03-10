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
const int MOD = 1e9+7;
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
vi primes;
int spf[300000]; //cache smallest prime factor of i
void sieve(int N) {
    for (int i=2;i<=N;i++)
        if (!spf[i]) {
            spf[i] = i;
            primes.pb(i);
            for (int j=2*i;j<=N;j+=i)
                if (!spf[j])
                    spf[j] = i;
        }
}
vpii prime_factorization(int i) {
    vpii res;
    while(i != 1) {
        if (!sz(res) || spf[i] != res.back().F) res.pb({spf[i],1});
        else res.back().S++;
        i /= spf[i];
    }
    return res;
}
ll exp(ll x, ll y) {
    ll res = 1;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1)
            res = (res*x) % MOD;
        y = y>>1;
        x = (x*x) % MOD;
    }
    return res;
}
multiset<int> p[20000];
vpii a[210000];
int main()
{
    setIO();
    sieve(210000);
    int n,q;cin>>n>>q;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        a[i] = prime_factorization(x);
        for (auto val: a[i])
            p[val.F].insert(val.S);
    }
    ll gcd = 1;
    for (int i=0;i<20000;i++)
        if (sz(p[i]))
            gcd = (gcd*exp(primes[i],*p[i].begin())) % MOD;
        cout << gcd << '\n';
    while(q--) {

    }

    return 0;
}
//REMEMBER TO DELETE UNUSED BEFORE SUBMITING - NO templates allowed


