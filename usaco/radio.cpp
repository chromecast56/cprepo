#include <bits/stdc++.h>

using namespace std;

int N,M;
struct point
{
    int x,y;
};
string mj,mb;
int dp[1001][1001];
point f[1001], b[1001];
point move(point src, char d)
{
    if (d=='N') src.y++;
    if (d=='W') src.x--;
    if (d=='S') src.y--;
    if (d=='E') src.x++;

    return src;
}
int dist(int i, int j)
{
    return (f[i].x-b[j].x)*(f[i].x-b[j].x) + (f[i].y-b[j].y)*(f[i].y-b[j].y);
}
int main()
{
    ofstream fout("radio.out");
    ifstream fin("radio.in");

    fin >> N >> M;
    fin >> f[0].x >> f[0].y;
    fin >> b[0].x >> b[0].y;
    fin >> mj >> mb;

    for (int i=1;i<=N;i++)
        f[i] = move(f[i-1],mj[i-1]);

    for (int i=1;i<=M;i++)
        b[i] = move(b[i-1],mb[i-1]);

    for (int i=0;i<=N;i++)
        for (int j=0;j<=M;j++)
        {
            if (!i&&!j) continue;
            int val = INT_MAX;
            if (i)
                val = min(val,dp[i-1][j]);
            if (j)
                val = min(val,dp[i][j-1]);
            if (i&&j)
                val = min(val,dp[i-1][j-1]);
            dp[i][j] = val + dist(i,j);
        }

    fout << dp[N][M] << "\n";
    return 0;
}