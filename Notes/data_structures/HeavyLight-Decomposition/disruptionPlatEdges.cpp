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
    //static int n;
    vl t,lazy;

    void init(/*vi &arr*/) {
        //n = arr.size();
        t = vl(n*4, INT_MAX);
        lazy = vl(n*4);
    }
    void push(int v) { //push changes from vertex v (note, you do have to push in modification queries)
        if (!lazy[v]) return;
        t[2*v] = lazy[v];
        lazy[2*v] = lazy[v];
        t[2*v+1] = lazy[v];
        lazy[2*v+1] = lazy[v];
        lazy[v] = 0;
    }
    void upd(int l,int r,ll val,int tl=0,int tr=n,int v=1) {
        if (l>r) return;
        if (tl==l && tr==r)
            t[v] = val, lazy[v] = t[v];
        else {
            push(v);
            int tm = (tl+tr)/2;
            upd(l,min(tm,r),val,tl,tm,v*2);
            upd(max(tm+1,l),r,val,tm+1,tr,v*2+1);
            t[v] = min(t[2*v],t[2*v+1]);
        }
    }
    int get(int ind,int tl=0,int tr=n,int v=1) {
        if (tl==ind&&tr==ind)
            return t[v];
        //push(v);
        int tm = (tl+tr)/2;
        if (ind <= tm) return get(ind,tl,tm,v*2);
        else return get(ind,tm+1,tr,v*2+1);
    }
};
struct HLD {
    vl parent, depth, head, pos, sz; //parent = parent node, depth = depth,
    //heavy = the heavy child of i (assume adj[u][0], head = head of current chain, pos = position in the segtree, out = out pos in dfs order
    int cur_pos;
    segtree seg;
    /*
            NOTE: All operations assume root = 0!
            HLD constructor takes in an array of verticie values, and an adj list.
            To modify for edges, add edge val to parent[]
     */
    HLD(vector<vl> &adj /*,vi &val*/) { //in this case, initial vals are unvisited (INT_MAX)
        int n = adj.size();
        parent = vl(n); parent[0] = -1;
        depth = vl(n); head = vl(n);
        pos = vl(n); sz = vl(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
        /*vi arr(n);
        for (int i=0;i<n;i++)
            arr[pos[i]] = val[i];*/
        /*
                On edges: do arr[pos[i]] = (pos[i]==0? -1 : edge(pos[i],parent[pos[i]])
                Each verticie is 1/1 with edge to its parent, besides root node (n -> n-1)
         */
        seg.init(/*arr*/);
    }
    int query(int a,int b) {
        if (depth[a]<depth[b]) swap(a,b);
        return seg.get(pos[a]);
    }
    void pathUpd(int a, int b, int val) {
        for (; head[a] != head[b]; b = parent[head[b]]) { //query full chains until a/b are in the same chain
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            seg.upd(pos[head[b]], pos[b], val);
            /*if (head[b] != 0)
                seg.upd(pos[head[b]],pos[head[b]]+1,val);*/
        }
        if (depth[a] > depth[b])
            swap(a, b);
        seg.upd(pos[a]+1, pos[b], val); //query last chain
    }
    void dfs(int v, vector<vl> &adj) {
        sz[v] = 1;
        for (auto &c : adj[v])
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                dfs(c,adj); sz[v] += sz[c];
                if (sz[c] > sz[adj[v][0]] || depth[c] > depth[adj[v][0]]) //stupid edge case - when adj[v][0] is the parent edge
                    swap(c,adj[v][0]);
            }
    }
    //v = verticie, h = the current head node of the verticie
    void decompose(int v, int h, vector<vl> const& adj) {
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
vector<vl> G;
int main()
{
    //ofstream fout("disrupt.out");
    //ifstream fin("disrupt.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vpll edges;
    cin>>n>>m;
    G.resize(n);
    for (int i=0;i<n-1;i++) {
        int a,b;cin>>a>>b;
        a--,b--;
        edges.pb({a,b});
        G[a].pb(b);
        G[b].pb(a);
    }

    HLD hld(G);
    vector<vi> backpaths;
    for (int i=0;i<m;i++)  {
        int a,b,w;
        cin>>a>>b>>w;
        a--,b--;
        backpaths.pb({-w,a,b});
    }

    sort(backpaths.begin(),backpaths.end());
    for (auto bp: backpaths)
        hld.pathUpd(bp[1],bp[2],-bp[0]);

    for (auto edge: edges) {
        int res = hld.query(edge.F,edge.S);

        cout << (res==INT_MAX? -1:res) << '\n';
    }

    return 0;
}