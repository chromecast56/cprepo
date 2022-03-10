#include <bits/stdc++.h>

using namespace std;

int N,H;
long long dp[1 << 20]; //for every config, find max 'safe factor'
struct cow
{
    long long h,w,s; //height, weight, strength
};
vector<cow> C(20);
int main()
{
    ofstream fout("guard.out");
    ifstream fin("guard.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin >> N >> H;
    for (int i=0;i<N;i++)
    {
        long long h,w,s;
        fin >> h >> w >> s;
        C[i] = {h,w,s};
    }

    memset(dp,-1,sizeof(dp));
    dp[0] = LONG_LONG_MAX; //no cows means we can put anything

    for (int msk=0;msk<(1 << N);msk++)
    {
        long long W = 0;
        for (int i=0;i<N;i++) //compute weight sum
            if (msk & (1 << i))
                W += C[i].w;

        for (int i=0;i<N;i++)
            if (!(msk & (1 << i)))
            {
                int nmsk = msk | (1 << i);
                long long max_carry = min(dp[msk],C[i].s - W); //max extra weight can carry if cow i on bottom

                dp[nmsk] = max(dp[nmsk], max_carry);
            }
    }

    long long res = -1;
    for (int msk=0;msk<(1 << N);msk++)
    {
        long long height = 0;
        for (int i=0;i<N;i++)
            if (msk & (1 << i))
                height += C[i].h;

        if (height >= H)
            res = max(res,dp[msk]);
    }

    if (res==-1)
        fout << "Mark is too tall\n";
    else
        fout << res << "\n";

    return 0;
}