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
struct BIT {
    ll bit[500000];
    void add(int idx, int val) {
        for (++idx; idx < 500000; idx += idx & -idx)
            bit[idx] += val;
    }
    void range_add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }

    ll operator[](int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }
};
vpii queries[500000]; //for every r in query (l,r), store possible l
int res[500000];
BIT bit;
int bs(int l,int r,int val) { //search for val in monotonic bit 3 3 2 1 1 0
    while(l<r) {
        int m = (l+r+1)>>1;
        if (bit[m] < val) r=m-1;
        else if (bit[m] >= val) l=m;
    }
    return l;
}
int main()
{
    setIO();
    int n,q;cin>>n>>q;
    vi a(n+1);
    for (int i=1;i<=n;i++)
        cin>>a[i], a[i] = i-a[i];

    for (int i=0;i<q;i++) {
        int x,y;cin>>x>>y;
        int l=x+1,r = n-y;
        queries[r].pb({l,i});
    }

    //now, iterate on r, while storing all possible suffixes along the way. Use BIT to update in logn time
    for (int r=1;r<=n;r++) {
        if (0 <= a[r] && a[r] < r) {
            int x = bs(1,r,a[r]); //find largest index st. bit[x] > a[r], meaning all prefix of 0 to x is incremented by 1

            if (bit[x] >= a[r]) //make sure we don't upd if we can't
                bit.range_add(1,x,1);
        }

        for (auto nd: queries[r]) {
            int l = nd.F, i = nd.S;
            res[i] = bit[l];
        }
    }

    for (int i=0;i<q;i++)
        cout << res[i] << '\n';

    return 0;
}
