/*
ID: jamesli5
PROG: nocows
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;


int main()
{
    ofstream fout("nocows.out");
    ifstream fin("nocows.in");

    int N,K;
    int dp[201][101] {0};
    fin >> N >> K;


    for(int i=1; i<=N; i++) {
        for(int j=1; j<=K; j++) {
            if(i == 1) dp[i][j] = 1;
            else {
                for(int l=1; l <= i-2; l++)
                    dp[i][j] += dp[l][j-1] * dp[i-l-1][j-1];
                dp[i][j] %= 9901;
            }
        }
    }


    fout << (dp[N][K] - dp[N][K-1] + 9901)%9901 << "\n";
    return 0;
}