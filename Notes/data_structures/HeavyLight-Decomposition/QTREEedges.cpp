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

int n;
struct segtree {
    //static int n;
    vl t;

    void init(vi &arr) {
        //n = arr.size();
        t = vl(n*4);
        for (int i=0;i<n;i++)
            upd(i,arr[i]);
    }
    void upd(int ind,ll val,int tl=0,int tr=n,int v=1) {
        if (tl==ind&&tr==ind)
            t[v] = val;
        else {
            int tm = (tl+tr)/2;
            if (ind <= tm) upd(ind,val,tl,tm,v*2);
            else upd(ind,val,tm+1,tr,v*2+1);
            t[v] = max(t[v*2],t[v*2+1]);
        }
    }
    int get(int l,int r,int tl=0,int tr=n,int v=1) {
        if (l>r) return -1;
        if (tl==l && tr==r)
            return t[v];
        else {
            int tm = (tl+tr)/2;
            return max(get(l,min(tm,r),tl,tm,v*2),
            get(max(tm+1,l),r,tm+1,tr,v*2+1));
        }
    }
};
struct HLD {
    vl parent, depth, head, pos, sz; //parent = parent node, depth = depth,
    //heavy = the heavy child of i (assume adj[u][0], head = head of current chain, pos = position in the segtree, out = out pos in dfs order
    vl e;
    int cur_pos;
    segtree seg;
    /*
            NOTE: All operations assume root = 0!
            HLD constructor takes in an array of verticie values, and an adj list.
            To modify for edges, add edge val to parent[]
     */
    HLD(vector<vpll> &adj /*,vi &val*/) { //in this case, initial vals are unvisited (INT_MAX)
        int n = adj.size();
        parent = vl(n); parent[0] = -1;
        depth = vl(n); head = vl(n);
        pos = vl(n); sz = vl(n);
        e = vl(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
        vi arr(n);
        for (int i=0;i<n;i++)
            arr[pos[i]] = pos[i] == 0? -1 : e[i];
        /*
                On edges: do arr[pos[i]] = (pos[i]==0? -1 : edge(pos[i],parent[pos[i]])
                Each verticie is 1/1 with edge to its parent, besides root node (n -> n-1)
         */
        seg.init(arr);
    }
    void upd(int a, int b,int val) {
        if (depth[a]>depth[b]) swap(a,b);
        return seg.upd(pos[b],val);
    }
    int pathQuery(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) { //query full chains until a/b are in the same chain
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            res = max(res, seg.get(pos[head[b]], pos[b]));
            /*if (head[b] != 0)
                seg.upd(pos[head[b]],pos[head[b]]+1,val);*/
        }
        if (depth[a] > depth[b])
            swap(a, b);
        res = max(res, seg.get(pos[a]+1, pos[b])); //query last chain
        return res;
    }
    void dfs(int v, vector<vpll> &adj) {
        sz[v] = 1;
        for (auto &edge : adj[v])
            if (edge.F != parent[v]) {
                int c = edge.F, w = edge.S;
                parent[c] = v, e[c] = w, depth[c] = depth[v] + 1;
                dfs(c,adj); sz[v] += sz[c];
                if (sz[c] > sz[adj[v][0].F] || depth[c] > depth[adj[v][0].F]) //stupid edge case - when adj[v][0] is the parent edge
                    swap(edge,adj[v][0]);
            }
    }
    //v = verticie, h = the current head node of the verticie
    void decompose(int v, int h, vector<vpll> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        for (auto c : adj[v])
            if (depth[c.F]>depth[v]) {
                if (c == adj[v][0])
                    decompose(c.F,h,adj);
                else
                    decompose(c.F,c.F,adj);
            }
    }

};
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        cin>>n;
        vector<vpll> G(n);
        vpii edge(1);
        for (int i=0;i<n-1;i++) {
            int a,b,w;cin>>a>>b>>w;
            a--,b--;
            G[a].pb({b,w});
            G[b].pb({a,w});
            edge.pb({a,b});
        }
        HLD hld(G);
        string typ; cin>>typ;
        while(typ != "DONE") {
            int a,b;cin>>a>>b;
            if (typ=="CHANGE")
                hld.upd(edge[a].F,edge[a].S,b);
            if (typ=="QUERY")
                cout << hld.pathQuery(--a,--b) << '\n';
            cin>>typ;
        }
    }

    return 0;
}