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
template<typename T>
struct segment_tree {
    int n;
    vector<T> segtree;
    function<T(const T&,const T&)> join;
    T base = T();
    segment_tree(int n, function<T(const T&,const T&)> join, T base = T()) : n(n), join(join), base(base){
        segtree.resize(n << 1, base);
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
        }
    }
    segment_tree(vector<T> seq, function<T(const T&,const T&)> join, T base = T()) : n(seq.size()), join(join), base(base){
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) {
            segtree[n + i] = seq[i];
        }
        build();
    }
    void update(int l,int r, ll val){
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                segtree[l] = join(segtree[l], val);
                ++l;
            }
            if (r & 1) {
                --r;
                segtree[r] = join(segtree[r], val);
            }
            l >>= 1;
            r >>= 1;
        }
    }
    T query(int pos) {
        pos+=n;
        ll ans = segtree[pos];
        pos>>=1;
        while(pos){
            ans = join(segtree[pos], ans);
            pos>>=1;
        }
        return ans;
    }
};
struct HLD {
    vl parent, depth, head, pos, sz; //parent = parent node, depth = depth,
    //heavy = the heavy child of i (assume adj[u][0], head = head of current chain, pos = position in the segtree, out = out pos in dfs order
    int cur_pos;
    segment_tree<int> seg;

    /*
            NOTE: All operations assume root = 0!
            HLD constructor takes in an array of verticie values, and an adj list.
            To modify for edges, add edge val to parent[]
     */
    HLD(vector<vl> &adj, segment_tree<int> &seg) : seg(seg) { //in this case, initial vals are unvisited (INT_MAX)
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
    }
    int query(int a,int b) {
        if (depth[a]<depth[b]) swap(a,b);
        return seg.query(pos[a]);
    }
    void pathUpd(int a, int b, int val) {
        for (; head[a] != head[b]; b = parent[head[b]]) { //query full chains until a/b are in the same chain
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            seg.update(pos[head[b]], pos[b], val);
            /*if (head[b] != 0)
                seg.upd(pos[head[b]],pos[head[b]]+1,val);*/
        }
        if (depth[a] > depth[b])
            swap(a, b);
        seg.update(pos[a]+1, pos[b], val); //query last chain
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
    ofstream fout("disrupt.out");
    ifstream fin("disrupt.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vpll edges;
    fin>>n>>m;
    G.resize(n);
    for (int i=0;i<n-1;i++) {
        int a,b;fin>>a>>b;
        a--,b--;
        edges.pb({a,b});
        G[a].pb(b);
        G[b].pb(a);
    }

    vi identity(n,INT_MAX);
    segment_tree<int> seg(identity, [&](const int &x, const int &y){
        return x<y ? x : y;
    }, 2e9);

    HLD hld(G, seg);
    vector<vi> backpaths;
    for (int i=0;i<m;i++)  {
        int a,b,w;
        fin>>a>>b>>w;
        a--,b--;
        backpaths.pb({-w,a,b});
    }

    //sort(backpaths.begin(),backpaths.end());
    for (auto bp: backpaths)
        hld.pathUpd(bp[1],bp[2],-bp[0]);

    for (auto edge: edges) {
        int res = hld.query(edge.F,edge.S);
        fout << (res==INT_MAX? -1:res) << '\n';
    }

    return 0;
}