/*
ID: jamesli5
PROG: castle
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int dx[9], dy[9]; // only dx/y[1,2,4,8] are going to be used but this way is convenient
bool wall[51][51][9]; //same as above
bool v[51][51];
int n,m;
int search(int x,int y)
{
    if (v[x][y]) return 0;

    v[x][y] = true;
    int ret = 1;
    for (int i = 1; i <= 8; i*=2)
    {
        if (wall[x][y][i]) continue;
        ret += search(x+dx[i],y+dy[i]);
    }
    return ret;
}
bool edge_wall(int x,int y,int k) //remember that walls on the border can't be removed
{
    x += dx[k];
    y += dy[k];
    if (x < 1 || x > n || y < 1 || y > m)
        return 1;
    return 0;
}
int main()
{
    ofstream fout("castle.out");
    ifstream fin("castle.in");

    fin >> m >> n;

    dy[1] = -1; dx[2] = -1; dy[4] = 1; dx[8] = 1;

    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            int val;
            fin >> val;
            while (val > 0)
            {
                wall[i][j][val & -val] = 1;
                val -= val&-val;
            }
        }

    int num_rooms = 0;
    int max_room = 0;

    int max_room2 = 0;
    int x,y,dir;

    //find num rooms and max room
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!v[i][j])
            {
                num_rooms++;
                max_room = max(max_room, search(i,j));
            }

    //find optimal wall
    for (int j = m; j >= 1; j--)
        for (int i = 1; i <= n; i++)
            for (int k = 4; k >= 2; k/=2)
            {
                if (!wall[i][j][k]) continue;
                if (edge_wall(i,j,k)) continue;

                for(int i=1;i<=50;i++) for(int j=1;j<=50;j++) v[i][j] = 0; //reset v array

                wall[i][j][k] = 0; //temporarily remove wall
                int val = search(i,j);
                if (max_room2 <= val)
                    x = i, y = j, dir = k, max_room2 = val;

                wall[i][j][k] = 1;
            }

    fout << num_rooms << "\n";
    fout << max_room << "\n";
    fout << max_room2 << "\n";
    fout << x << ' ' << y << ' ' << (dir == 2? 'N' : 'E') << "\n";

    return 0;
}

