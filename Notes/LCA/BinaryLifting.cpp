#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int N = 100000;
const int LN = 14;
int depth[N], pa[LN][N];
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
void dfs(int cur,int prev,int _depth=0)
{
    pa[0][cur] = prev;
    depth[cur] = _depth;
    for (auto i: adj[cur])
        if (i != prev)
            dfs(i,cur,_depth+1);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> n >> q; //assume 1 is root
    for (int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i=0;i<LN;i++) for (int j=0;j<N;j++) pa[i][j] = -1;

    dfs(0,-1);
    for (int i=1;i<LN;i++)
        for (int j=0;j<N;j++)
            if (pa[i-1][j] != -1)
                pa[i][j] = pa[i-1][pa[i-1][j]];

    for (int i=0; i<q;i++) {
        int u,v;
        cin >> u >> v;
        cout << LCA(u,v) << '\n';
    }

    return 0;
}

