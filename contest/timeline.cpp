#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
const int maxn = 100100;

int n,m,c;
int s[maxn];
vector<pii> G[maxn];

vi start;
vi tsort;

int ans[maxn];
bool v[maxn];
void dfs(int u) {
    if (v[u]) return;
    v[u] = 1;
    for (auto ne: G[u]) dfs(ne.F);
    tsort.pb(u);
}
void toposort() {
    for (int i=1;i<=n;i++) if (!v[i]) dfs(i);
    reverse(tsort.begin(),tsort.end());
}
int main()
{
    ofstream fout("timeline.out");
    ifstream fin("timeline.in");
    ios_base::sync_with_stdio(false);
    fin.tie();

    fin>>n>>m>>c;
    for (int i=1;i<=n;i++) fin >> ans[i];
    for (int i=0;i<c;i++) {
        int a,b,x;
        fin>>a>>b>>x;
        G[a].pb({b,x});
    }
    toposort();

    for (auto cur: tsort) {
        for (auto ne: G[cur]) {
            ans[ne.F] = max(ans[ne.F],ans[cur]+ne.S);
        }
    }
    for (int i=1;i<=n;i++)
        fout << ans[i] << '\n';

    return 0;
}
