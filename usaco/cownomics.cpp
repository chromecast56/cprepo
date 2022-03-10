#include <bits/stdc++.h>

using namespace std;

int N,M;
char spot[500][500], plain[500][500];
long long h_sp[500], h_pl[500], r[500];
int main()
{
    ofstream fout("cownomics.out");
    ifstream fin("cownomics.in");

    fin >> N >> M;

    string x;
    for (int i=0;i<N;i++)
    {
        fin >> x;
        for (int j=0;j<M;j++)
            spot[i][j] = x[j];
    }
    for (int i=0;i<N;i++)
    {
        fin >> x;
        for (int j=0;j<M;j++)
            plain[i][j] = x[j];
    }
    for (int i=0;i<M;i++) //other idea: Instead of having to guarantee the uniqueness of each string (by poly hashing)
    {                       // a better idea is to simply have an array of random ints (c++ std::random()) to add and subtract by
                                //  Ex. a*r[0] + b*r[1] + c*r[2]... Rolling hash is much easier, just add/subtract a*r[0] or c*r[2]
        r[i] = rand() % 1000000007;
    }
    int i=0,j=0;
    bool works = 0;
    int res = M;
    while(j<M) //note to self: don't convert ATGC to 0123 with the random vector, clumps the hashes together
    {
        if (works)
            res = min(res,j-i);
        if (!works) //duplicates we need to extend
        {
            works = 1;
            unordered_set<long long> hs;
            for (int k = 0; k < N; k++) {
                h_sp[k] += r[j]*spot[k][j];
                h_pl[k] += r[j]*plain[k][j];
                hs.insert(h_sp[k]);
            }
            for (int k = 0; k < N; k++)
                if (hs.find(h_pl[k]) != hs.end())
                    works = 0;
            j++;
        }
        else { //no duplicates see if we can do better
            works = 1;
            unordered_set<long long> hs;
            for (int k = 0; k < N; k++) {
                h_sp[k] -= r[i]*spot[k][i];
                h_pl[k] -= r[i]*plain[k][i];
                hs.insert(h_sp[k]);
            }
            for (int k = 0; k < N; k++)
                if (hs.find(h_pl[k]) != hs.end())
                    works = 0;
            i++;
        }
    }
    fout << res << "\n";
    return 0;
}