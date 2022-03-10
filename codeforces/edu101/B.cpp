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
int main()
{
    setIO();
    int t;cin>>t;
    while(t--) {
        int n,k;cin>>n>>k;
        vl a;
        int res = 1;
        pll cstr = {0,0};
        for (int i=0;i<n;i++) {
            ll x;cin>>x; a.pb(x);
            if (i) cstr = {cstr.F-(k-1),cstr.S+(k-1)};
            else   cstr = {x,x};
            pll hcstr = {x,x+(k-1)};
            cstr = {max(cstr.F,hcstr.F),min(cstr.S,hcstr.S)};
            if (cstr.F > cstr.S) {res = 0;}
        }

        if (cstr.F > a.back() || cstr.S < a.back()) res = 0;
        cout << (res?"YES\n":"NO\n");
    }


    return 0;
}
//REMEMBER TO DELETE UNUSED BEFORE SUBMITING - NO templates allowed


