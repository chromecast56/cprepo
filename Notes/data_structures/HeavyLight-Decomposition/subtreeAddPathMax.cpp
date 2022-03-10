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
    static int n;
    vi t,lazy;

    void init(vi &arr) {
        n = arr.size();
        t.resize(arr.size()*4);
        lazy.resize(arr.size()*4);
        for (int i=0;i<n;i++)
            upd(i,i+1,arr[i]);
    }
    void push(int v) { //push changes from vertex v
        if (!lazy[v]) return;
        t[2*v] += lazy[v];
        lazy[2*v] += lazy[v];
        t[2*v+1] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int l,int r,int add,int tl=0,int tr=n,int v=1) {
        if (l>=r) return;
        if (tl==l && tr==r)
            t[v] += add, lazy[v] += add;
        else {
            push(v);
            int tm = (tl+tr)/2;
            upd(l,min(tm,r),add,tl,tm,v*2);
            upd(max(tm,l),r,add,tm,tr,v*2+1);
            t[v] = max(t[2*v],t[2*v+1]);
        }
    }
    int get(int l,int r,int tl=0,int tr=n,int v=1) {
        if (l>=r) return INT_MIN;
        if (l <= tl && tr <= r) return t[v];
        push(v);
        int tm = (tl+tr)/2;
        return max(get(l,min(tm,r),tl,tm,v*2),
                   get(max(l,tm),r,tm,tr,v*2+1));
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
        /*
                On edges: do arr[pos[i]] = (pos[i]==0? -1 : edge(pos[i],parent[pos[i]])
                Each verticie is 1/1 with edge to its parent, besides root node (n -> n-1)
         */
        seg.init(arr);
    }
    /*
            Subtree queries work by essentially combining the concept of Euler tour with HLD
            You arrange it so that all heavy paths are on the very right, allowing the segtree to satisfy euler tour
     */
    void subtreeUpd(int v,int val) {
        seg.upd(pos[v],pos[v]+sz[v],val);
    }
    int pathQuery(int a, int b) {
        int res = INT_MIN;
        for (; head[a] != head[b]; b = parent[head[b]]) { //query full chains until a/b are in the same chain
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int heavypath_ans = seg.get(pos[head[b]], pos[b]+1);
            res = max(res,heavypath_ans);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavypath_ans = seg.get(pos[a], pos[b]+1); //query last chain
        res = max(res,last_heavypath_ans);
        return res;
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
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    vector<vi> G(n);
    for (int i=0;i<n-1;i++) {
        int x,y; cin>>x>>y;
        x--,y--;
        G[x].pb(y);
        G[y].pb(x);
    }

    vi identity(n);
    HLD hld = HLD(identity,G);
    cin>>q;
    while(q--) {
        string x; int a,b;
        cin>>x>>a>>b;
        if (x=="add") {
            a--;
            hld.subtreeUpd(a, b);
        }
        else {
            a--,b--;
            cout << hld.pathQuery(a, b) << '\n';
        }
    }

    return 0;
}