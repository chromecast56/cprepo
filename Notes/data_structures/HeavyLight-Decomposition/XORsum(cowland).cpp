#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int MAXN = 100100;
const int LN = 17;
int n,q, costs[MAXN]; vi adj[MAXN];
int baseArray[MAXN], ptr=0;
int chainNo=0, chainInd[MAXN], chainHead[MAXN], posInBase[MAXN];
int depth[MAXN], f[LN][MAXN], size[MAXN];
namespace SegTree //Segment Tree data structure
{
    int st[6*MAXN];
    void build(int cur,int l,int r) { //use BaseArray[] to construct tree
        if (l+1==r) {
            st[cur] = baseArray[l];
            return;
        }
        int c1 = cur*2, c2 = cur*2+1, m = (l+r)/2;
        build(c1,l,m);
        build(c2,m,r);
        st[cur] = st[c1]^st[c2];
    }
    void update(int cur,int l,int r,int ind,int val) {
        if (l > ind || r <= ind) return;
        if (l==ind && r==ind+1) {
            st[cur] = val;
            return;
        }
        int c1 = cur*2, c2 = cur*2+1, m = (l+r)/2;
        update(c1,l,m,ind,val);
        update(c2,m,r,ind,val);
        st[cur] = st[c1] ^ st[c2];
    }
    int query(int cur,int l,int r,int L,int R) { //query in range [L,R), lowercase are helper var
        if (l >= R || r <= L)
            return 0;
        if (l >= L && r <= R)
            return st[cur];
        int c1 = cur*2, c2 = cur*2+1, m = (l+r)/2;
        int q1 = query(c1,l,m,L,R);
        int q2 = query(c2,m,r,L,R);
        return q1 ^ q2;
    }
}
int LCA(int u,int v) //find LCA of u and v
{
    if (depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for (int i=0;i<LN;i++) if (diff>>i&1) u = f[i][u];
    if (u==v) return u; //because if go on, will return parent instead
    for (int i=LN-1;i>=0;i--)
        if (f[i][u] != f[i][v]) //too far if meet same ancestor
            u = f[i][u],
            v = f[i][v];
    return f[0][u]; //return parent of u, since we get to as close as possible to LCA
}
int query_up(int u,int v) //given that v is ancestor of u, sum u to v
{                           //notice that this code is a bit different because the weights are on nodes, not edges
    int uchain, vchain = chainInd[v], ans = -1;
    while(1) {
        uchain = chainInd[u];
        if (uchain == vchain) { //same chain, segtree query part of it
            int q = SegTree::query(1,0,ptr,posInBase[v],posInBase[u]+1);
            if (ans==-1) ans = q;
            else ans ^= q;
            break;
        }
        //diff chain, query for entire
        int q = SegTree::query(1,0,ptr,posInBase[chainHead[uchain]],posInBase[u]+1);
        if (ans==-1) ans = q;
        else ans ^= q;

        u = chainHead[uchain]; //move u to head, then to beginning of next chain
        u = f[0][u];
    }
    return ans;
}
int query(int u,int v) //xor sum from u to v
{
    int lca = LCA(u,v);
    return query_up(u,lca) ^ query_up(v,lca) ^ costs[lca]; //note lca is double counted, have to xor again
}
void update(int u,int val) //update attraction value of node u
{
    costs[u] = val; //for query(u,v), not needed for segtree
    SegTree::update(1,0,ptr,posInBase[u],val);
}
void dfs(int cur,int prev,int _depth = 0) //dfs to precompute subtree sizes, depths
{
    f[0][cur] = prev;
    depth[cur] = _depth;
    size[cur] = 1;
    for (auto ne: adj[cur]) if (ne != prev) {
            dfs(ne,cur,_depth+1);
            size[cur] += size[ne];
        }
}
void HLD(int cur,int prev) //HLD to find most efficient Euler Tour for SegTree
{
    if (chainHead[chainNo] == -1)
        chainHead[chainNo] = cur;

    chainInd[cur] = chainNo; //given node, find its chain
    posInBase[cur] = ptr; //position of node in segment tree
    baseArray[ptr++] = costs[cur];

    int sc = -1; //find special child
    for (auto ne: adj[cur]) if (ne != prev)
            if (sc==-1 || size[sc] < size[ne])
                sc = ne;
    if (sc != -1) //continue into chain
        HLD(sc,cur);

    //create chains for all other children
    for (auto ne: adj[cur]) if (ne != prev && ne != sc) {
        chainNo++;
        HLD(ne,cur);
    }
}
int main()
{
//    ofstream fout("cowland.out");
//    ifstream fin("cowland.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> n >> q;
    for (int i=1;i<=n;i++) cin >> costs[i];
    for (int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(chainHead,-1,sizeof(chainHead));
    memset(f,-1,sizeof(chainHead));

    dfs(1,-1);
    HLD(1,-1);
    SegTree::build(1,0,ptr);
    //LCA dp
    for (int i=1;i<LN;i++)
        for (int j=1;j<=n;j++)
            if (f[i-1][j] != -1)
                f[i][j] = f[i-1][f[i-1][j]];

    while(q--) {
        int type,a,b;
        cin >> type >> a >> b;
        if (type==1)
            update(a,b);
        else
            cout << query(a,b) << '\n';
    }
    return 0;
}