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

int n,q;
struct segtree {
    vpll t;
    vl lazy; //a = min, b = sum
    void init(vl &arr) {
        t.resize(4*n);
        lazy.resize(4*n);

        for (int i=0;i<n;i++)
            add(i,i+1,arr[i]);
    }
    pll combine(pll a,pll b) {
        return {min(a.F,b.F),a.S+b.S};
    }
    void push(int v,int l,int m,int r) {
        if (!lazy[v]) return;
        t[2*v].F += lazy[v]; t[2*v].S += lazy[v]*(m-l);
        t[2*v+1].F += lazy[v]; t[2*v+1].S += lazy[v]*(r-m);
        lazy[2*v] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    void add(int l,int r,ll val,int tl=0,int tr=n,int v=1) {
        if (l>=r) return;
        if (l==tl&&r==tr) {
           t[v].F += val;
           t[v].S += val*(tr-tl);
           lazy[v] += val;
        }
        else {
            int tm = (tl+tr)/2;
            push(v,tl,tm,tr);

            add(l,min(tm,r),val,tl,tm,v*2);
            add(max(l,tm),r,val,tm,tr,v*2+1);
            t[v] = combine(t[2*v],t[2*v+1]);
        }
    }
    pll query(int l,int r,int tl=0,int tr=n,int v=1) { //return min and sum
        if (l>=r) return {INT_MAX,0};
        if (l==tl&&r==tr) return t[v];
        int tm = (tl+tr)/2;
        push(v,tl,tm,tr);

        return combine(query(l,min(tm,r),tl,tm,v*2), query(max(tm,l),r,tm,tr,v*2+1));
    }
};
int main()
{
    ofstream fout("haybales.out");
    ifstream fin("haybales.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>q;
    vl a(n);
    for (int i=0;i<n;i++) fin>>a[i];

    segtree seg;
    seg.init(a);
    while(q--) {
        char typ;fin>>typ;

        int a,b;fin>>a>>b;
        a--,b--;
        if (typ=='M')
            fout << seg.query(a,b+1).F << '\n';
        if (typ=='S')
            fout << seg.query(a,b+1).S << '\n';
        if (typ=='P') {
            int val;fin>>val;
            seg.add(a,b+1,val);
        }
    }


    return 0;
}