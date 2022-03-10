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
int n,p;
struct suffq { //change from max suffix to min prefix (MAKE X AND Y NEGATIVE :) )
    map<ll,ll> m;
    void ins(ll x,ll y) { //insert (x,y), but we want to maintaint the invariant that if x_1<x_2<x_3... then y_1>y_2>y_3...
        x = -x, y = -y;
        auto it = m.lb(x); if (it!=m.end() && it->S >= y) return; //irrelevant
        it = m.insert(it,{x,y});
        it->S = y; //????
        while(it != m.begin() && prev(it)->S <= y) m.erase(prev(it));
    }
    int query(ll x) { //query maximum y in the set st. the x val >= x... Because of our invariant we can simply do a lower_bound (y decreases)
        x = -x;
        auto it = m.lb(x);
        if (it==m.end()) return 0; //x bigger than all m[i].x
        return -it->S;
    }
};
struct query {
    ll x,y,b,i;
    bool operator<(const query &a)const{if(x==a.x)return y<a.y;return x<a.x;}
};
ll f[100100];
/*
            NOTE: Main problem was that before I didn't split the queries into begin/end... Just remember this for next time
            Why it doesn't work? Well say you process a query, but it then leads to (1 bil, y) where y is relatively small.
            Then, on the next query, the suffix data structure will take that absurd endpoint into account even if it shouldn't!

 */
int main()
{
    setIO("boards");
    cin>>n>>p;
    vector<query> b;
    for (int i=0;i<p;i++) {
        int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        b.pb({x1,y1,0,i});
        b.pb({x2,y2,1,i});
    }
    b.pb({n,n,0,p}); sort(all(b));
    suffq suf; suf.ins(0,0);
    for (auto q: b)
        if (!q.b) { //starting point, query
            f[q.i] = q.x+q.y + suf.query(q.y);
        }
        else {
            suf.ins(q.y, f[q.i]-q.x-q.y);
        }

    cout << f[p] << '\n';

    return 0;
}
