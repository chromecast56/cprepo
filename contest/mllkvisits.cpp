#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int N = 100100;
const int LN = 50;
int depth[N], pa[LN][N];
int sum[N];
int a[N];
vi adj[N];
int n,q;
int LCA(int u,int v)
{
    if (depth[u] < depth[v]) {int t=u;u=v;v=t;}
    int diff = depth[u] - depth[v];
    for (int i=0;i<ceil(log2(n));i++) if ((diff>>i)&1) u = pa[i][u];
    if (u==v) return u;
    for (int i=LN-1;i>=0;i--)
        if (pa[i][u] != pa[i][v]) {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}
void dfs(int cur,int prev,int _depth=0, int _sum=0)
{
    pa[0][cur] = prev;
    depth[cur] = _depth;
    sum[cur] = _sum;
    for (auto i: adj[cur])
        if (i != prev)
            dfs(i,cur, _depth+1, _sum+a[i]);
}
int main()
{
    ofstream fout("milkvisits.out");
    ifstream fin("milkvisits.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    fin >> n >> q; //assume 1 is root
    string x;
    fin>>x;
    for (int i=1;i<=n;i++)
        if (x[i-1]=='H') a[i] = 0;
        else           a[i] = 1;

    for (int i=0;i<n-1;i++) {
        int u,v;
        fin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(pa,-1,sizeof(pa));

    sum[1] = a[1];
    dfs(1,-1);
    for (int i=1;i<LN;i++)
        for (int j=0;j<N;j++)
            if (pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];

    x.clear();
    for (int i=0; i<q;i++) {
        int u,v; char c;
        fin >> u >> v >> c;
        int lca = LCA(u,v);
        int num_nodes = depth[u]+depth[v]-2*depth[lca]+1;
        int num_milk = sum[u]+sum[v]-2*sum[lca]+a[lca];

        if (c=='H' && num_milk != num_nodes) x += '1';
        else if (c=='G' && num_milk != 0) x += '1';
        else                              x += '0';
    }

    fout << x << '\n';

    return 0;
}