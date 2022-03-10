#include <bits/stdc++.h>

using namespace std;
const int MAX = 251;

int N,M;
long long G[MAX][MAX];
long long D[MAX];
int p[MAX];
bool v[MAX];
long long dijskra(int src)
{
    for (int i=1;i<=N;i++)
        D[i] = (1ll << 50), p[i] = -1, v[i] = 0;

    D[src] = 0;
    for (int cnt=0;cnt<N-1;cnt++)
    {
        long long min = (1ll<<50), min_i = -1;
        for (int i=1;i<=N;i++)
            if (!v[i] && D[i] <= min)
                min = D[i], min_i = i;

        v[min_i] = 1;
        for (int i=1;i<=N;i++)
            if (!v[i] && D[min_i] + G[min_i][i] < D[i])
                D[i] = D[min_i] + G[min_i][i], p[i] = min_i;
    }
    return D[N];
}
int main()
{
    ofstream fout("rblock.out");
    ifstream fin("rblock.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems


    fin >> N >> M;
    for (int i=1;i<=N;i++) {
        for (int j=1;j<=N;j++)
            G[i][j] = (1ll << 50);
        G[i][i] = 0;
    }

    for (int i=0;i<M;i++)
    {
        int a,b,w;
        fin >> a >> b >> w;
        G[a][b] = w;
        G[b][a] = w;
    }

    //dijskra w/ backtracking
    dijskra(1);
    vector<int> P;
    for (int i=0;i<=N;i++) //record parents
        P.push_back(p[i]);

    long long res1 = D[N], res2 = 0;

    int ch = N;
    while(ch != 1)
    {
        int par = P[ch];
        G[ch][par] *= 2;
        G[par][ch] *= 2;
        res2 = max(res2,dijskra(1));
        G[ch][par] /= 2;
        G[par][ch] /= 2;

        ch = par;
    }

    fout << res2-res1 << '\n';

    return 0;
}