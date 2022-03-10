/*
ID: jamesli5
PROG: numtri
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int dp[1000][1000];
int main()
{
    ofstream fout("numtri.out");
    ifstream fin("numtri.in");

    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            fin >> dp[i][j];

    for (int i = n-2; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[i][j] += max(dp[i+1][j],dp[i+1][j+1]);

    fout << dp[0][0] << "\n";

    return 0;
}

