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
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

//1. HLD :)
//2. Path queries to see if number exists... segment tree with hashset in the background
/*

 */
vector<vi> G;
int n,m;
vi typ;
/*
            HLD assumes segtree queries are of type [l,r)
 */
struct segtree {
    vector<unordered_set<int>> t;
    void init(vi &arr) {
        t.resize(arr.size()*4);
        build(arr);
    }
    bool query(int l,int r, int val, int tl=0,int tr=n, int v=1) { //value, cur l/r bounds, overall l/r bounds
        if (l >= r) return 0;
        if (tl == l && tr == r) return t[v].find(val) != t[v].end();
        int tm = (tl+tr)/2;
        return query(l,min(tm,r),val,tl,tm,v*2) || query(max(tm,l),r,val,tm,tr,v*2+1);
    }
    void build(vi &arr,int l=0,int r=n,int v=1) { //build from pos array
        if (l+1==r) t[v].insert(arr[l]);
        else {
            int m = (l+r)>>1;
            build(arr,l,m,v*2);
            build(arr,m,r,v*2+1);

            for (auto a: t[2*v]) t[v].insert(a);
            for (auto a: t[2*v+1]) t[v].insert(a);
        }
    }

};
struct HLD {
    vi parent, depth, heavy, head, pos; //parent = parent node, depth = depth,
    //heavy = the heavy child of i, head = head of current chain, pos = position in the segtree
    int cur_pos;
    segtree seg;
    /*
            NOTE: All operations assume root = 0!
            HLD constructor takes in an array of verticie values, and an adj list.
            To modify for edges, add edge val to parent[]
     */
    HLD(vi &val, vector<vi> const& adj) {
        int n = adj.size();
        parent = vi(n); parent[0] = -1;
        depth = vi(n);
        heavy = vi(n,-1); head = vi(n);
        pos = vi(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
        vi arr(n);
        for (int i=0;i<n;i++)
            arr[pos[i]] = val[i];

        /*
                On edges: do arr[pos[i]] = (pos[i]==0? -1 : edge(pos[i],parent[pos[i]])
                Each verticie is 1/1 with edge to its parent, besides root node (n -> n-1)
         */
        seg.init(arr);
    }
    int query(int a, int b,int col) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int heavypath_ans = seg.query(pos[head[b]], pos[b]+1, col);
            res |= heavypath_ans;
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavypath_ans = seg.query(pos[a], pos[b]+1, col);
        res |= last_heavypath_ans;
        return res;
    }
    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }

    int decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }

};
int main()
{
    ofstream fout("milkvisits.out");
    ifstream fin("milkvisits.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>m;
    G.resize(n);
    typ.resize(n);
    for (int i=0;i<n;i++) fin>>typ[i];
    for (int i=0;i<n-1;i++) {
        int a,b;fin>>a>>b;
        a--,b--;
        G[a].pb(b);
        G[b].pb(a);
    }

    HLD hld(typ,G);
    string res;
    for (int i=0;i<m;i++) {
        int a,b,c; fin>>a>>b>>c;
        a--,b--;
        res.pb(hld.query(a,b,c) + '0');
    }

    //queries
    fout << res << '\n';

    return 0;
}
