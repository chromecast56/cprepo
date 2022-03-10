#include <bits/stdc++.h>

using namespace std;

int dp[2][11000000];//CHANGE TO 10M
int main()
{
    ofstream fout("feast.out");
    ifstream fin("feast.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    int T,A,B;
    fin >> T >> A >> B;

    int res = 0;
    for (int i=0;i<2;i++)
        for (int j=0;j<=T;j++)
        {
            if (j==0) dp[i][j] = 1;

            if (dp[i][j])
            {
                res = max(res,j);
                dp[i][j+A] = 1;
                dp[i][j+B] = 1;

                if (i==0)
                    dp[1][j/2] = 1;
            }
        }

    fout << res <<  '\n';
    return 0;
}