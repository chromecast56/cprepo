#include <bits/stdc++.h>

using namespace std;

int N,T;
int g[100][100];
long long D[100][100][3];
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};
struct state
{
    int x,y,t;
};
int main()
{
    ofstream fout("visitfj.out");
    ifstream fin("visitfj.in");

    fin >> N >> T;

    for (int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            fin >> g[i][j];

    queue<state> q;
    state begin {0,0,0};
    q.push(begin);

    while(!q.empty())
    {
        state cur = q.front();
        q.pop();


        for (int i = 0; i < 4; i++)
        {
            int nx = cur.x+dx[i], ny = cur.y+dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) //check if inbounds
                continue;
            int time_add = cur.t==2? g[nx][ny] : 0; //amt of time eating grass
            long long new_d = D[cur.x][cur.y][cur.t] + T + time_add; //new dist

            if (D[nx][ny][(cur.t+1)%3] == 0 || D[nx][ny][(cur.t+1)%3] > new_d) //distance relaxing
            {
                D[nx][ny][(cur.t+1)%3] = new_d;
                state next {nx,ny,(cur.t+1)%3};
                q.push(next);
            }
        }
    }
    //min of the three ending states
    fout << min(min(D[N-1][N-1][0],D[N-1][N-1][1]),D[N-1][N-1][2]) << "\n";

    return 0;
}

