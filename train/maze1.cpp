/*
ID: jamesli5
PROG: maze1
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int W,H;
char g[201][77];
int D[201][77];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int search(int x,int y)
{
    for (int i=1;i<2*H;i+=2)
        for (int j=1;j<2*W;j+=2)
            D[i][j] = 0;

    queue<pair<int,int>> q;
    q.push(make_pair(x,y));
    while(!q.empty())
    {
        pair<int,int> cur = q.front(); q.pop();
        for (int i=0;i<4;i++)
        {
            x = cur.first, y = cur.second;
            if (g[x+dx[i]][y+dy[i]] != ' ') continue; //is wall

            if (x+dx[i]==2*H || x+dx[i]==0 || y+dy[i]==2*W || y+dy[i]==0)
                return D[x][y] + 1;
            if (D[x+2*dx[i]][y+2*dy[i]]) continue;

            D[x+2*dx[i]][y+2*dy[i]] = D[x][y] + 1;
            q.push(make_pair(x+2*dx[i],y+2*dy[i]));
        }
    }
    return 1000000000;
}
int main()
{
    ofstream fout("maze1.out");
    ifstream fin("maze1.in");


    fin >> W >> H;
    for (int i=0;i<=2*H;i++)
    {
        fin.get();
        for (int j=0;j<=2*W;j++)
            g[i][j] = fin.get();

    }

    int res = 1;
    for (int i=1;i<2*H;i+=2)
        for (int j=1;j<2*W;j+=2)
            if (g[i][j] == ' ')
                res = max(res, search(i, j));


    fout << res << "\n";
    return 0;
}