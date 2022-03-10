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

/*
        Documentation

        Basically, this is a regular BIT. But, instead of integers, we store segment trees
        This allows us to stretch into the 2nd dimension, albiet with severe restrictions.

        We can:
            - Modify/add a horzontail line of numbers (single y, since regular BIT can only handle point updates)
            - Query the sum on a submatrix (multiple y, analagous to prefix sum query)

        This is an improvement to the point update, submatrix query problem
        However, it cannot solve the submatrix update submatrix query problem.

        Note: The Segment Tree is built on demand, so we dont use absurd amts of memory


        Maintain a 2D BIT on the farm, update each segment, john is t ahead...
        The main part of the problem is implementing the 2D BIT with range queries and range updates
        Here, first layer is a BIT and 2nd layer (in each BIT) is a segtree, except it is allocated on demand.
 */
int n,t;
#define MAXV 100100
//node of the segtree (w lazy prop)
struct node {
    ll val;
    struct node* C[2];

    node() {
        val = 0;
        C[0] = C[1] = NULL;
    }
    node* getc(int c) {
        if (!C[c])
            C[c] = new node;
        return C[c];
    }
    void add(int l,int r,int v,int tl=0,int tr=MAXV) {
        if (l>=r) return;
        if (l==tl&&r==tr) val += v;
        else {
            int tm = (tl+tr)/2;
            getc(0)->add(l,min(tm,r),v,tl,tm);
            getc(1)->add(max(l,tm),r,v,tm,tr);;
        }
    }
    ll get(int ind,int tl=0,int tr=MAXV) {
        if (tl+1==tr) return val;
        int tm = (tl+tr)/2;
        if (ind<tm) return val + getc(0)->get(ind,tl,tm);
        else        return val + getc(1)->get(ind,tm,tr);
    }
};
struct BIT2D {
    vector<node> BT;
    BIT2D() {
        BT.resize(MAXV);
    }
    //typical, keep. Submatrix [x1,x2]*[0,y] += v
    void addU(int x1,int x2,int y,int v) {
        if (x1>x2) return;
        for (y++; y < MAXV; y += y&-y)
            BT[y].add(x1,x2+1,v);
    }
    //add a horizontal segment (or remove if d=-1)
    void add(int x1,int x2,int y, int d = 1) {
        addU(x1,x2,y,d);
    }

    //typical, keep. Sum up [x]*[0,y]
    ll getU(int x, int y) {
        ll res = 0;
        /*for (y++; y > 0; y -= y&-y)               //if you need range queries
            res += BT[y].get(x1,x2+1);*/
        for (y++; y > 0; y -= y&-y)
            res += BT[y].get(x);
        return res;
    }
    //query with vertical segment
    ll get(int x,int y1,int y2) {
        return getU(x,y2) - (y1? getU(x,y1-1):0);
    }
};
struct point {
    int x,y;
};
struct seg {
    point a,b;
    bool bo; //horz or vertical
    int t; //time
    seg(point aa,point bb,int tt) {
        bo = aa.x==bb.x;
        if ((!bo && aa.x>bb.x) || (bo && aa.y>bb.y))
            swap(aa,bb);
        a = aa; b = bb; t = tt;
    }
};
vector<seg> v;
vi x,y; //coordinate compression
unordered_map<int,int> x_to_i,y_to_i;
void coord_compress() {
    for (auto &seg: v) {
        x.pb(seg.a.x), x.pb(seg.b.x);
        y.pb(seg.a.y), y.pb(seg.b.y);
    }
    sort(all(x)); sort(all(y));
    x.erase(unique(all(x)),x.end());
    y.erase(unique(all(y)),y.end());
    for (int i=0;i<sz(x);i++) x_to_i[x[i]] = i;
    for (int i=0;i<sz(y);i++) y_to_i[y[i]] = i;
    for (auto &seg: v) {
        seg.a.x = x_to_i[seg.a.x]; seg.b.x = x_to_i[seg.b.x];
        seg.a.y = y_to_i[seg.a.y]; seg.b.y = y_to_i[seg.b.y];
    }
}
int main()
{
    ofstream fout("mowing.out");
    ifstream fin("mowing.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>t;
    point a;
    fin>>a.x>>a.y;

    for (int i=0;i<n-1;i++) {
        point b; fin>>b.x>>b.y;
        v.pb(seg(a,b,i));
        a = b;
    }

    coord_compress();
    ll res = 0;
    BIT2D bit;
    //first do add horz, query vert
    for (int i=0;i<n-1;i++) {
        if (v[i].bo)
            res += bit.get(v[i].a.x,v[i].a.y +1,v[i].b.y -1);
        if (i>=t && !v[i-t].bo)
            bit.add(v[i-t].a.x +1,v[i-t].b.x -1,v[i-t].a.y);
    }
    for (int i=0;i<MAXV;i++) bit.BT[i]=node();
    //add vert, query horz
    for (int i=0;i<n-1;i++) {
        if (!v[i].bo)
            res += bit.get(v[i].a.y,v[i].a.x +1,v[i].b.x -1);
        if (i>=t && v[i-t].bo)
            bit.add(v[i-t].a.y +1,v[i-t].b.y -1,v[i-t].a.x);
    }

    fout << res << '\n';

    return 0;
}