#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

const int MAXN = 100010;
const int M = 30;
int f[MAXN][M]; //dp: for seq (0,i) ending in M, find min cost. (M=0 corr to global f(i))
int G[M][M]; //graph of all (i,j) combo changes, later optimized in Floyd-Warshall
int p[MAXN][M]; //store prefix sum of cost to change seq (0,i) to letter M

int n,m,K;
int main()
{
//    ofstream fout("cowmbat.out");
//    ifstream fin("cowmbat.in");
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin >> n >> m >> K;
    string x; cin>>x;
    for (int i=0;i<n;i++) x[i] = x[i] - 'a' + 1;

    for (int i=1;i<=m;i++)
        for (int j=1;j<=m;j++)
            cin >> G[i][j];

    //floyd warshall
    for (int k=1;k<=m;k++) for (int i=1;i<=m;i++) for (int j=1;j<=m;j++)
        if (G[i][k] + G[k][j] < G[i][j])
            G[i][j] = G[i][k] + G[k][j];

    //psum
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++)
            p[j][i] = (x[j-1] == i? 0:G[x[j-1]][i])  +  p[j-1][i];

    for (int i=0;i<MAXN;i++) fill(f[i],f[i]+M,1000000000);
    f[0][0] = 0;
    for (int i=K;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            f[i][j] = f[i-K][0] + (p[i][j]-p[i-K][j]); //make a subsequence of length k
            f[i][j] = min(f[i][j],f[i-1][j] + (x[i-1]==j?0:G[x[i-1]][j])); //or add one to a previous one

            f[i][0] = min(f[i][0],f[i][j]); //update global ans for subseq
        }

    }
    cout << f[n][0] << '\n';
    return 0;
}