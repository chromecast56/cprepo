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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
struct station {
    int x,r,f;
    bool operator <(station &a) {return r>a.r;} //sort by range
};
Tree<int> fset[11000]; //array by freq list, and each ost stores x vals
int main()
{
    setIO();
    int n,k; cin>>n>>k;
    vector<station> vec;
    for (int i=0;i<n;i++) {
        int x,r,f;cin>>x>>r>>f;
        vec.pb({x,r,f});
    }

    sort(all(vec));
    ll res = 0; //originally a 2d range sum problem, but since k is small we can just loop on second dimension
    for (auto &cur: vec) { //loop sorted by range (so if we see one, the know that it will intersect)
        for (int i=max(0,cur.f-k);i<=cur.f+k;i++) { //loop over poss frequencies (doable since k is small)
            //want to get all elements in range [cur.x-cur.r,cur.x+cur.r]
            res += fset[i].order_of_key(cur.x+cur.r+1) - fset[i].order_of_key(cur.x-cur.r);
        }
        fset[cur.f].insert(cur.x);
    }
    cout<<res<< '\n';

    return 0;
}
