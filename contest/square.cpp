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
int n;
vpll a;
vl X,Y;
ll pow2[210];
unordered_set<ll> hashset;
map<ll,vl> freq; //do set for now, log optimize later
void compute(ll x,ll y,ll dx,ll dy) {
    ll hash = 0;
    for (int j=0;j<n;j++) {
        pll cur = {a[j].F-x,a[j].S-y};
        cur = {cur.F*dx,cur.S*dy};
        if (min(cur.F,cur.S) >= 0)
            freq[max(cur.F,cur.S)].pb(j);
    }
    hashset.insert(hash);
    for (auto &vec: freq) {
        for (auto &val: vec.S) {
            hash = (hash+pow2[val])%MOD;
        }
        hashset.insert(hash);
    }
    freq.clear();
}
int main()
{
    cin>>n;
    for (int i=0;i<n;i++) {
        ll x,y;
        cin>>x>>y;
        a.pb({x,y});
        X.pb(x),Y.pb(y);
    }
    pow2[0] = 1;
    for (int i=1;i<n;i++) pow2[i] = (2*pow2[i-1])%MOD;

    sort(X),sort(Y);
    for (auto x: X) {
        for (auto y: Y) {
            compute(x,y,1,1);
            compute(x,y,1,-1);
            compute(x,y,-1,1);
            compute(x,y,-1,-1);
        }
    }
    cout << sz(hashset) << '\n';

    return 0;
}
