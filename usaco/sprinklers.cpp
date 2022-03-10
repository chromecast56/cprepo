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
int n;
vpii aa,bb,a,b;
int main()
{
    //setIO("sprinklers");

    cin>>n;
    for (int i=0;i<n;i++) {
        int x,y;cin>>x>>y;
        aa.pb({x,y}); bb.pb({x,y});
    }

    //process into convex hull
    sort(all(aa)); sort(all(bb));
    int mono = aa[0].S;
    for (int i=1;i<n;i++)
        if (aa[i].S > mono) aa[i].F = -1;
        else mono = aa[i].S;
    mono = bb[n-1].S;
    for (int i=n-2;i>=0;i--)
        if (bb[i].S < mono) bb[i].F = -1;
        else mono = bb[i].S;
    for (int i=0;i<n;i++) { //like xor... if both, then degenerate intersection
        if (aa[i].F!=-1 && bb[i].F==-1) a.pb(aa[i]);
        if (bb[i].F!=-1 && aa[i].F==-1) b.pb(bb[i]);
    }

    ll res = 0;
    int it1=0,it2=0;
    for (int i=a[0].F+1;i<=b.back().F;i++) {
        ll l = b[it2].S-a[it1].S;
        res += l*(l+1)>>1;

    }


    return 0;
}
