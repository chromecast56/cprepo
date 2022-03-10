/*
ID: jamesli5
PROG: subset
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

long long dp[1000];
int main()
{
    ofstream fout("subset.out");
    ifstream fin("subset.in");

    int n;
    fin >> n;

    int sum = n*(n+1)/2;
    if (sum % 2 ==1)
    {
        fout << "0\n";
        return 0;
    }
    sum /= 2;

    for (int i = 1; i <= n; i++)
    {
        for (int j = sum; j >= i; j--)
            dp[j] += dp[j-i];

        dp[i]++;
    }
    fout << dp[sum]/2 << "\n";
    return 0;
}