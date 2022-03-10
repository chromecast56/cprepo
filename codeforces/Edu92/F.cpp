#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
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
struct seg {
    int l,r,t,i; //index, bool for starting, color (start = 0 to be in front in sorting)
};
bool comp(seg a,seg b) {
    if(a.r==b.r) return a.l<b.l;return a.r<b.r;
}
struct segtree {
    ll t[4*MX];
    void upd(int ind,int val,int tl=0,int tr=MX,int v=1) {
        if (tl+1==tr) t[v] = val;
        else {
            int tm = (tl+tr)>>1;
            if (ind < tm)
                upd(ind,val,tl,tm,v*2);
            else
                upd(ind,val,tm,tr,v*2+1);
            t[v] = max(t[v*2],t[v*2+1]);
        }
    }
    ll query(int l,int r,int tl=0,int tr=MX,int v=1) {
        if (l >= r) return 0;
        if (l==tl&&r==tr) return t[v];
        else {
            int tm = (tl+tr)>>1;
            return max(query(l,min(tm,r),tl,tm,v*2),query(max(tm,l),r,tm,tr,v*2+1));
        }
    }
};
segtree st[2];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;cin>>n;
    vector<seg> a;
    for (int i=0;i<n;i++) {
        int l,r,t;cin>>l>>r>>t;
        t--;
        a.pb({l,r,t,-1});
    }
    sort(a.begin(),a.end(),comp);

    vector<seg> as[2]; //a seperate
    for (int i=0;i<n;i++) {
        a[i].i = i;
        as[a[i].t].pb(a[i]);
    }

    int res=0;
    for (int i=0;i<n;i++) { //fi = fj+1 if seg[j].r < seg[i].l for all oppo color, if j<i for same color
        bool c = a[i].t;
        seg test = {0,a[i].l,-1,-1};
        auto lb = lower_bound(as[c^1].begin(),as[c^1].end(), test, comp);
        int bd = lb==as[c^1].end()? i : lb->i; //convert to index, if end then just get everything

        //query max over same color, dif color. If same, just check all below, if dif, use the lb for a boundary
        int q = max(st[c].query(0,i),
                st[c^1].query(0,bd));
        st[c].upd(i,q+1);

        res = max(res,q+1);
        cout << "dbg: " << q+1 << '\n';
    }
    cout << res << '\n';

    return 0;
}