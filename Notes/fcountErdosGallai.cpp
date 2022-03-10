/*
            Erdos Gallai Theorem:
            Given a list of the number of neighbors each node in a graph has, ordered by:
                d_1 >= d_2 >= d_3 ... >= d_n

            The graph can be validly created iff:
                - The sum of d_1 to d_n is even     (handshake theorem)
                - The inequality:
                    sum(i,k) {d_i} <= k(k-1) + sum(k+1,n) {min(k,d_i)}
                  is satisfied for all 1 <= k <= n

        Time complexity is O(n^2), but is reduced to O(n) if prefix sums are computed

        For the entire problem we simply temporarily delete each node and compute Erdos Galai's theorem on the
        resulting graph.
 */

#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> res;
struct s
{
    int v,i;
    s(int vv,int ii) {
        v=vv;i=ii;
    }
    bool operator<(const s &a) const {
        return v >= a.v;
    }
};
vector<s> A;
int main()
{
    ofstream fout("fcount.out");
    ifstream fin("fcount.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    A.push_back(s(1000000000,-1));
    fin >> N;
    for (int i=1;i<=N+1;i++)
    {
        int v; fin >> v;
        A.push_back(s(v,i));
    }
    sort(A.begin(),A.end());

    for (int i=1;i<=N+1;i++)
    {
        vector<s> f = A;
        f.erase(f.begin()+i);

        bool works = 1;

        int s = 0;
        for (int j=1;j<=N;j++)
            s += f[j].v;
        if (s % 2 == 1) {
            works = 0;
            continue;
        }

        for (int k=1;k<=N;k++)
        {
            int s1=0,s2=k*(k-1);

            for (int j=1;j<=N;j++) {
                if (j <= k) s1 += f[j].v;
                else s2 += min(k,f[j].v);
            }
            if (s1 > s2)
                works = 0;
        }
        if (works)
            res.push_back(A[i].i);
    }
    sort(res.begin(),res.end());
    fout << res.size() << '\n';
    for (auto &v: res)
        fout << v << '\n';

    return 0;
}