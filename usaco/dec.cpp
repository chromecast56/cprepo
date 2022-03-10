#include <bits/stdc++.h>

using namespace std;

int dp[1 << 20]; //CHANGE TO 20

int N,M;
int C[20][20];

struct bonus
{
    int p,a;
    bonus(int pp,int aa) {
        p=pp;a=aa;
    }
};
vector<bonus> B[21]; //for each k, store p and a
int main()
{
    ofstream fout("dec.out");
    ifstream fin("dec.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin >> N >> M;
    for (int i=0;i<M;i++)
    {
        int k,p,a;
        fin >> k >> p >> a;
        B[k].push_back(bonus(p,a));
    }

    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
        {
            int v; fin >> v;
            C[i][j] = v;
        }

    dp[0] = 0;
    for (int msk=1;msk<(1<<N);msk++)
    {
        //count num cows used, i.e. next event number
        int evnum = 0;
        for (int i=0;i<N;i++)                  //alternative quick method is evnum = __builtin_popcount(msk)
            if (msk & (1<<i))
                evnum++;

        //dp to find max
        for (int i=0;i<N;i++)
            if (msk & (1<<i))
            {
                int bmsk = msk-(1<<i);
                int nv = dp[bmsk] + C[i][evnum-1];

                dp[msk] = max(dp[msk],nv);
            }

        //add in awards
        for (auto &b: B[evnum])
            if (dp[msk] >= b.p)
                dp[msk] += b.a;
    }

    fout << dp[(1<<N)-1] << '\n';


    return 0;
}