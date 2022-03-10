/*

                    BIG TIP: When dealing with dp problems that go from 0 <= i <= N
                    (instead of 1<=i<=N or 0<=i<N)
                    It's a good idea to do dp(i+1) compared to dp(i) rather than
                    dp(i) compared to dp(i-1)

                    Add an if(i>0) or if(i<N) when neccessary

 */

#include <bits/stdc++.h>

using namespace std;

int H,G;
pair<int,int> h[1001], g[1001];
long long dp[1001][1001][2]; //num holsteins, num geursneys, whether end on holstein or geursney
int dist(pair<int,int> &a, pair<int,int> &b)
{
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
}
int main()
{
    ofstream fout("checklist.out");
    ifstream fin("checklist.in");

    fin >> H >> G;

    for (int i=0;i<H;i++) fin >> h[i].first >> h[i].second;
    for (int i=0;i<G;i++) fin >> g[i].first >> g[i].second;

    for(int i = 0; i <= H; i++) {
        for(int j = 0; j <= G; j++) {
            dp[i][j][0] = dp[i][j][1] = 1L << 60;
        }
    }
    dp[1][0][0] = 0;
    for(int i = 0; i <= H; i++) {
        for(int j = 0; j <= G; j++) {
            for(int k = 0; k < 2; k++) {
                if(k == 0 && i == 0) continue;
                if(k == 1 && j == 0) continue;

                pair<int,int> src = k? g[j-1] : h[i-1];
                if(i < H) {
                    dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][k] + dist(src,h[i]));
                }
                if(j < G) {
                    dp[i][j+1][1] = min(dp[i][j+1][1], dp[i][j][k] + dist(src,g[j]));
                }
            }
        }
    }
    fout << dp[H][G][0] << "\n";

    return 0;
}