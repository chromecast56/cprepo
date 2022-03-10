/*
ID: jamesli5
PROG: inflate
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int dp[10001]; //max number of points that sum to weight i
int p[10001], w[10001];
int main()
{
    ofstream fout("inflate.out");
    ifstream fin("inflate.in");

    int M,N;
    fin >> M >> N;
    for (int i=0;i<N;i++)
        fin >> p[i] >> w[i];

    for (int i=0;i<N;i++)
        for (int j=1;j<=M;j++)
        {
            if (j == w[i] || (j >= w[i] && dp[j-w[i]]))
                dp[j] = max(dp[j], dp[j-w[i]] + p[i]);
        }
    int res = 0;
    for (int i=0;i<=M;i++) //take global max, since problem is 0/1, dp[M] is not neccessarily max
        res = max(res,dp[i]);

    fout << res << "\n";
    return 0;
}