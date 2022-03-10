/*
ID: jamesli5
PROG: ttwo
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;

char g[10][10];
int dx[] = {-1,0,1,0};
int dy[]= {0,1,0,-1};
bool v[10][10][4][10][10][4];
struct point
{
    int x,y,d;
};
bool in(int x,int y)
{
    return x>=0&&x<10&&y>=0&&y<10&&g[x][y]!='*';
}
int main()
{
    ofstream fout("ttwo.out");
    ifstream fin("ttwo.in");


    point f,c;
    for (int i=0;i<10;i++)
    {
        fin >> g[i];
        for (int j=0;j<10;j++)
            if(g[i][j]=='F') f = {i,j,0};
            else if (g[i][j]=='C') c = {i,j,0};
    }
    int res = 0;

    v[f.x][f.y][f.d][c.x][c.y][c.d] = 1;
    while(f.x != c.x || f.y != c.y)
    {
        if (in(f.x+dx[f.d],f.y+dy[f.d]))
        {
            f.x += dx[f.d];
            f.y += dy[f.d];
        }
        else f.d = (f.d+1)%4;

        if (in(c.x+dx[c.d],c.y+dy[c.d]))
        {
            c.x += dx[c.d];
            c.y += dy[c.d];
        }
        else c.d = (c.d+1)%4;
        res++;

        if (v[f.x][f.y][f.d][c.x][c.y][c.d])
        {
            res = 0;
            break;
        }
        v[f.x][f.y][f.d][c.x][c.y][c.d] = 1;
    }
    fout << res << "\n";
    return 0;
}