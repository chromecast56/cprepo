#include <bits/stdc++.h>

using namespace std;

int N;
int x[25000], y[25000];
bool v[25000];
void dfs(int P, int ind)
{
    if (v[ind]) return;
    v[ind] = 1;
    for (int i=0;i<N;i++)
        if ((x[ind]-x[i])*(x[ind]-x[i])+(y[ind]-y[i])*(y[ind]-y[i]) <= P)
            dfs(P,i);
}
bool reach_all()
{
    for (int i=0;i<N;i++)
        if (!v[i])
            return 0;
    return 1;
}
int main()
{
    ofstream fout("moocast.out");
    ifstream fin("moocast.in");

    fin >> N;
    for (int i=0;i<N;i++)
        fin >> x[i] >> y[i];

    int lo = 0, hi = INT_MAX;

    while(lo < hi)
    {
        int mid = (lo+hi)/2;
        memset(v,0,sizeof(v));
        dfs(mid,0);

        if (reach_all())
            hi = mid;
        else
            lo = mid+1;
    }
    fout << lo << "\n";

    return 0;
}