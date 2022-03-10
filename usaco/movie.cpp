#include <bits/stdc++.h>

using namespace std;

int N,L;
int dp[1 << 20];
int D[20];
vector<int> mov[20];
int bsearch(int i, int t) //given a movie type, find its latest showing that starts before time t
{
    int lo = 0, hi = mov[i].size()-1;

    while(lo < hi)
    {
        int mid = (lo+hi+1)/2;
        if (mov[i][mid] <= t)
            lo = mid;
        else
            hi = mid-1;
    }
    return mov[i][lo] <= t? mov[i][lo] : -1;
}
int main()
{
    ofstream fout("movie.out");
    ifstream fin("movie.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL);

    fin >> N >> L;
    for (int i=0;i<N;i++)
    {
        int d,num;
        fin >> d >> num;
        for (int j=0;j<num;j++)
        {
            int s; fin >> s;
            mov[i].push_back(s);
        }
        D[i] = d;
    }

    for (int i=0;i<(1 << N); i++)
        dp[i] = -1;

    dp[0] = 0;
    int res = 21;
    for (int msk = 0; msk < (1 << N); msk++)
    {
        if (dp[msk] == -1) continue;

        if (dp[msk] >= L) {
            int num = 0;
            for (int i = 0; i < N; i++)
                if (msk & (1 << i))
                    num++;

            res = min(res,num);
        }
        for (int i=0;i<N;i++)
        {
            if (msk & (1 << i)) //we've seen this movie
                continue;

            int nmsk = msk + (1 << i);
            int latest_showing = bsearch(i,dp[msk]);

            if (latest_showing == -1) //can't go here
                continue;

            dp[nmsk] = max(dp[nmsk], latest_showing + D[i]);
        }
    }

    fout << (res == 21? -1: res) << "\n";
    return 0;
}