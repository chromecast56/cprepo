/*
ID: jamesli5
PROG: money
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int N,V;
int v[26];
long long dp[10001];
int main()
{
    ofstream fout("money.out");
    ifstream fin("money.in");

    fin >> V >> N;
    for (int i=0;i<V;i++)
        fin >> v[i];

    dp[0] = 1;
    for (int j=0;j<V;j++)
        for (int i=1;i<=N;i++)
        {
            if (v[j] > i) continue;
            dp[i] += dp[i-v[j]];
        }
    fout << dp[N] << "\n";
    return 0;
}