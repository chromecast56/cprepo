#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
const int maxn = 1010;
const int UNVISITED = -1000000000;

int n,m,c;
vi M(maxn);
vi G[maxn];
int f[maxn][maxn]; //f(n,t) = n'th node, t days, max cost.   NOTE: n=0 is global max
int dp[maxn]; //dp(t) = msx cost of loop to 1 for time t

bool v[maxn];
int main()
{
    ofstream fout("time.out");
    ifstream fin("time.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    fin>>n>>m>>c;
    for (int i=1;i<=n;i++)
        fin >> M[i];

    for (int i=0;i<m;i++) {
        int a,b;
        fin>>a>>b;
        G[a].pb(b);
    }
    for (int i=0;i<maxn;i++) fill(f[i],f[i]+maxn, UNVISITED);

    f[1][0] = 0;
    for (int t=0;t<1000;t++) {
        for (int i=1;i<=n;i++)
            if (f[i][t] != UNVISITED)
                for (auto ne: G[i]) {
                    f[ne][t + 1] = max(f[ne][t + 1], f[i][t] + M[ne]);
                }

    }

    int res = 0;
    for (int t=0;t<=1000;t++) {
        if (f[1][t] != UNVISITED)
            res = max(res, f[1][t]-c*t*t);
    }
    fout << res << '\n';

    return 0;
}