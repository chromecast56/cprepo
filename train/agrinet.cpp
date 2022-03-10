/*
ID: jamesli5
PROG: agrinet
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int N;
int G[100][100];
bool v[100];
int D[100]; //distance from indicie to other node, usually a parent array would be used to determine other node
int main()
{
    ofstream fout("agrinet.out");
    ifstream fin("agrinet.in");

    fin >> N;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            fin >> G[i][j];

    for (int i=0;i<N;i++)
        D[i] = 1000000000;

    D[0] = 0;
    int res = 0;
    for (int i=0;i<N-1;i++)
    {
        int min = 1000000000, min_i = 1000000000;
        for (int j=0;j<N;j++)
            if (!v[j] && min > D[j])
                min = D[j], min_i = j;

        v[min_i] = 1;
        for (int j=0;j<N;j++)
            if (G[min_i][j] && !v[j] && D[j] > G[min_i][j])
                D[j] = G[min_i][j];
    }
    for (int i=1;i<N;i++)
        res += D[i];

    fout << res << "\n";
    return 0;
}