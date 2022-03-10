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

int n,m;
struct segtree {
    vi t; //t isnt actually a t array for range sums, it is "for l,r, add t[v] to answer"

    void init(vi &arr) {
        n = arr.size();
        t.resize(arr.size()*4);
        for (int i=0;i<n;i++)
            upd(i,i+1,arr[i]);
    }
    void upd(int l,int r,int val,int tl=0,int tr=n,int v=1) {
        if (l>=r) return;
        if (tl==l && tr==r)
            t[v] += val;
        else {
            int tm = (tl+tr)/2;
            upd(l,min(tm,r),val,tl,tm,v*2);
            upd(max(tm,l),r,val,tm,tr,v*2+1);
        }
    }
    int get(int ind,int tl=0,int tr=n,int v=1) {
        if (tl==ind&&tr==ind+1)
            return t[v];
        int tm = (tl+tr)/2;
        if (ind<tm)
            return t[v] + get(ind,tl,tm,v*2);
        else
            return t[v] + get(ind,tm,tr,v*2+1);
    }
};
struct HLD {
    vi parent, depth, head, pos, sz; //parent = parent node, depth = depth,
    //heavy = the heavy child of i (assume adj[u][0], head = head of current chain, pos = position in the segtree, out = out pos in dfs order
    int cur_pos;
    segtree seg;
    /*
            NOTE: All operations assume root = 0!
            HLD constructor takes in an array of verticie values, and an adj list.
            To modify for edges, add edge val to parent[]
     */
    HLD(vi &val, vector<vi> &adj) {
        int n = adj.size();
        parent = vi(n); parent[0] = -1;
        depth = vi(n); head = vi(n);
        pos = vi(n); sz = vi(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
        vi arr(n);
        for (int i=0;i<n;i++)
            arr[pos[i]] = val[i];
        seg.init(arr);
    }
    int get(int ind) {
        return seg.get(pos[ind]);
    }
    void pathUpd(int a, int b) {
        for (; head[a] != head[b]; b = parent[head[b]]) { //query full chains until a/b are in the same chain
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            seg.upd(pos[head[b]], pos[b]+1,1);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        seg.upd(pos[a], pos[b]+1,1); //query last chain
    }
    void dfs(int v, vector<vector<int>> &adj) {
        sz[v] = 1;
        for (auto &c : adj[v])
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                dfs(c,adj); sz[v] += sz[c];
                if (sz[c] > sz[adj[v][0]])
                    swap(c,adj[v][0]);
            }
    }
    //v = verticie, h = the current head node of the verticie
    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        for (int c : adj[v])
            if (depth[c]>depth[v]) {
                if (c == adj[v][0])
                    decompose(c,h,adj);
                else
                    decompose(c,c,adj);
            }
    }

};
int main()
{
    ofstream fout("maxflow.out");
    ifstream fin("maxflow.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>m;
    vector<vi> G(n);
    for (int i=0;i<n-1;i++) {
        int a,b; fin>>a>>b;
        a--,b--;
        G[a].pb(b);
        G[b].pb(a);
    }

    vi identity(n);
    HLD hld(identity,G);
    for (int i=0;i<m;i++) {
        int a,b;fin>>a>>b;
        a--,b--;
        hld.pathUpd(a,b);
    }

    int res = 0;
    for (int i=0;i<n;i++)
        res = max(res,hld.get(i));
    fout << res << '\n';

    return 0;
}