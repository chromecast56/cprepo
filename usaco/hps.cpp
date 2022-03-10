#include <bits/stdc++.h>

using namespace std;

int N,K;
int a[100001]; //prefix sum for hoof, paper, siss
int dp[100001][21][3]; //max wins for subs(1,N) with k switches, ending on color c
int main()
{
    ofstream fout("hps.out");
    ifstream fin("hps.in");

    fin >> N >> K;
    for (int i=1;i<=N;i++)
    {
        char c; fin >> c;
        if (c=='H') a[i] = 0;
        if (c=='P') a[i] = 1;
        if (c=='S') a[i] = 2;
    }

    for (int i=1;i<=N;i++)
        for (int j=0;j<=K;j++)
            for (int c=0;c<3;c++)
            {
                if (j==0)
                    dp[i][j][c] = dp[i-1][j][c] + (a[i] == c? 1:0);
                else
                {

                    int ostate1 = (c + 1) % 3;
                    int ostate2 = (c + 2) % 3;
                    dp[i][j][c] = max(max(dp[i-1][j][c], dp[i-1][j-1][ostate1]), dp[i-1][j-1][ostate2]) + (a[i] == c ? 1 : 0);
                }
            }

    fout << max(max(dp[N][K][0],dp[N][K][1]),dp[N][K][2]) << "\n";

    return 0;
}