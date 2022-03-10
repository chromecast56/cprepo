#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define pb push_back

template <class t>
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

int n,d;
const int N = 1010;
int res[N][N], fin[N][N];
struct pt {
    int x,y,t;
    pt upd(int d) {return {x,y,t+d};}
    bool operator<(const pt &a) const {return t>a.t;} //sort by decreasing radius
};
vector<pt> centers[N];
int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
int in(int x,int y) {
    return x > 0 && y > 0 && x <= n && y <= n;
}
int D[N][N]; //distance to nearest wall,
void bfs_wall(deque<pt> &q) {
    while(!q.empty()) {
        pt cur = q.front();q.pop_front();
        for (int i=0;i<4;i++) {
            pt nxt = {cur.x+dx[i],cur.y+dy[i]};
            if (in(nxt.x,nxt.y) && D[nxt.x][nxt.y] == 1000000)
                D[nxt.x][nxt.y] = D[cur.x][cur.y]+1,
                q.push_back(nxt);
        }
    }
}
void print_arr(int (&arr)[N][N]) {
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++)
            cout << arr[i][j];
        cout << endl;
    }
}
int compute(deque<pt> &q) {
    int limit = 1;
    deque<pt> next_q;
    while(!q.empty()) {
        pt cur = q.front(); q.pop_front();
        if (cur.t == limit*d) limit++;
        for (int i=0;i<4;i++) {
            pt nxt = {cur.x+dx[i],cur.y+dy[i],cur.t};
            if (in(nxt.x,nxt.y) && D[nxt.x][nxt.y] >= limit && !res[nxt.x][nxt.y]) {
                res[nxt.x][nxt.y] = limit;
                if (nxt.t+1==limit*d) { //case where we see if we can expand
                    if (D[nxt.x][nxt.y] >= limit+1)
                        res[nxt.x][nxt.y] = limit+1,
                            q.pb(nxt.upd(1));
                }
                else
                    q.pb(nxt.upd(1));
            }
        }
    }
    for (int i=0;i<n;i++) {
        dp[i] = dp[i-1] + cost_cow;
    }
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (res[i][j]) centers[res[i][j]].pb({i,j}), fin[i][j] = 1;
    for (int i=n/2;i>=1;i--) {
        swap(q,next_q);
        next_q.clear();
        for (auto cur: q) {
            for (int dif=0;dif<4;dif++) {
                pt nxt = {cur.x+dx[dif],cur.y+dy[dif]};
                if (in(nxt.x,nxt.y) && !fin[nxt.x][nxt.y])
                    next_q.pb(nxt), fin[nxt.x][nxt.y] = 1;
            }
        }
        for (auto cur: centers[i])
            next_q.pb(cur);
    }
    int output = 0;
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (fin[i][j]) output++;
    return output;
}
int main()
{
    cin>>n>>d;

    for (int i=0;i<N;i++) for (int j=0;j<N;j++) D[i][j] = 1000000;
    deque<pt> qWall,qSrc;
    for (int i=1;i<=n;i++) {
        string x;cin>>x;
        for (int j=0;j<n;j++) {
            if (x[j] == '#')
                qWall.pb({i,j+1}),
                D[i][j+1] = 0;
            if (x[j] == 'S')
                qSrc.pb({i,j+1}),
                res[i][j+1] = 1;
        }
    }
    bfs_wall(qWall);
    cout << compute(qSrc) << '\n';

    return 0;
}