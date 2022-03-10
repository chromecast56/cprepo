#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

int n,m;
vector<pii> G[101];
int v[101];
vi f[101]; //dp on edges
int ff[101]; //maxes of dp on edges (dp on verticies)
vi tsort;
void dfs(int cur) {
    if (v[cur]) return;
    v[cur] = 1;
    for (auto ne: G[cur]) dfs(ne.F);
    tsort.pb(cur);
}
void toposort() {
    for (int i=1;i<=n;i++)
        if (!v[i]) dfs(i);
 //   reverse(tsort.begin(),tsort.end());
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>m;
    for (int i=0;i<m;i++) {
        int a,b; char c;
        cin>>a>>b>>c;
        G[a].pb({b,c});
        f[a].pb(0);
    }

    toposort();
    for (auto cur: tsort) {
        int m = 0;
        for (int i=0;i<G[cur].size();i++) {
            pii e = G[cur][i];
            bool b = 0;
            int max_d = 0;
            for (int j=0;j<G[e.F].size();j++) {
                pii ee = G[e.F][j];
                if (ee.S >= e.S) b=1, max_d = max(max_d,f[e.F][j]);
            }
            if (!b) f[cur][i] = 1;
            else f[cur][i] = max_d+1;

            m = max(m,f[cur][i]);
        }
        ff[cur] = m;
    }
    for (int i=1;i<=n;i++) {
        string x = "";
        for (int j=1;j<=n;j++) x += (ff[i]>ff[j]? 'A':'B');
        cout << x << '\n';
    }


    return 0;
}