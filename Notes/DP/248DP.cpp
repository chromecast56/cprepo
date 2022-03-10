#include <bits/stdc++.h>

using namespace std;

int dp[250][250]; //max val for segment (i,j)
int G[250];
int N;
int main()
{
    ofstream fout("248.out");
    ifstream fin("248.in");

    fin >> N;

    for (int i=0;i<N;i++)
        fin >> G[i];

    int res = 0;
    for (int len=1;len<=N;len++)
        for (int i=0; i+len<=N;i++)
        {
            int j = i+len-1;

            if (i==j) dp[i][j] = G[i]; //base case, one letter
            else dp[i][j] = -1; //usually dp[i][j] = dp[i][j-1] but isnt needed

            for (int k=i;k<j;k++)
                if (dp[i][k] != -1 && dp[i][k] == dp[k+1][j])
                    dp[i][j] = max(dp[i][j], dp[i][k]+1);

            res = max(res,dp[i][j]);
        }

    fout << res << "\n";
    return 0;
}
