/*
ID: jamesli5
PROG: cowtour
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;
const int MAX = 1000000000;

int N;
int x[150],y[150];
double D[150][150];
int g[150][150], c[150];
void fill(int ind, int color)
{
    if (c[ind]) return;
    c[ind] = color;
    for (int i = 0; i < N; i++)
        if (g[ind][i])
            fill(i,color);
}
double dist(int i,int j)
{
    return sqrt(abs(x[i]-x[j])*abs(x[i]-x[j]) + abs(y[i]-y[j])*abs(y[i]-y[j]));
}
int main()
{
    ofstream fout("cowtour.out");
    ifstream fin("cowtour.in");

    fin >> N;
    for (int i=0;i<N;i++)
        fin >> x[i] >> y[i];

    for (int i=0;i<N;i++) {
        fin.get();
        for (int j = 0; j < N; j++) {
            g[i][j] = fin.get()-'0';
        }
    }
    int color = 0;
    for (int i=0;i<N;i++)
        if (!c[i])
            fill(i,++color);


    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (g[i][j] && i!=j)
                D[i][j] = dist(i,j);
            else
                D[i][j] = MAX;

    for (int k=0;k<N;k++)
        for (int i=0;i<N;i++)
            for (int j=0;j<N;j++)
                if (D[i][k]+D[k][j] < D[i][j] && i!=j&&j!=k&&i!=k)
                    D[i][j] = D[i][k] + D[k][j];

    double res = MAX;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
        {
            if (c[i]==c[j]) continue;
            double m_i = 0, m_j = 0;
            for(int k=0;k<N;k++)
            {
                if (D[i][k] != MAX && m_i < D[i][k]) m_i = D[i][k];
                if (D[j][k] != MAX && m_j < D[j][k]) m_j = D[j][k];
            }
            double dia = m_i+m_j+ dist(i,j);
            res = min(res,dia);
        }

    //EDGE CASE: You can link two fields together and get a min, but if another one naturally has a bigger diameter
    //then you can't ignore it
    //This doesn't seem to be infered in the problem statement but the official solution takes it into account
    for (int i=0;i<N;i++)
    {
        double m_i;
        for(int k=0;k<N;k++)
            if (D[i][k] != MAX && m_i < D[i][k]) m_i = D[i][k];

        if (res < m_i)
            res = m_i;
    }

    fout << fixed << setprecision(6) << res << "\n";
    return 0;
}