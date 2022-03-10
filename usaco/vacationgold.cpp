#include <bits/stdc++.h>

using namespace std;
#define maxn 20001
#define inf 1e9

int d[2][200][maxn]; //for/back, hub, which node
int hb[200];
int n,m,k,Q;
struct edge
{
    int b,w; //dest, weight
    bool operator<(const edge &a) const {
        return w<a.w;
    }
};
vector<edge> g[maxn], gr[maxn];
queue<edge> q;
void add_edge(int a,int b,int w)
{
    edge e {b,w};
    g[a].push_back(e);
    e = {a,w};
    gr[b].push_back(e);
}
void dijskra(int ind,bool b) //note: for some dumb reason dijskra only gets 4/10 (TLE), while SPFA gets 10/10
{
    vector<edge> *G = b? gr:g;
    fill(d[b][ind],d[b][ind]+maxn,inf);
    d[b][ind][hb[ind]] = 0;
    q.push({hb[ind],0});

    while(!q.empty())
    {
        int cur = q.front().b;
        q.pop();
        for(auto &ne: G[cur])
            if (d[b][ind][ne.b] > d[b][ind][cur] + ne.w) {
                d[b][ind][ne.b] = d[b][ind][cur] + ne.w;
                q.push({ne.b,d[b][ind][ne.b]});
            }
    }
    while(!q.empty()) q.pop();
}
int main()
{
    ofstream fout("vacationgold.out");
    ifstream fin("vacationgold.in");

    ios_base::sync_with_stdio(false); //faster I/O
    fin.tie(NULL); //include only for non-interactive problems

    fin>>n>>m>>k>>Q;

    while(m--) {
        int a,b,w; fin>>a>>b>>w;
        add_edge(a,b,w);
    }
    for(int i=0;i<k;i++) {
        int a; fin>>a;
        hb[i] = a;
    }

    for(int i=0;i<k;i++) {
        dijskra(i,0);
        dijskra(i,1);
    }
    /*for (int i=1;i<=n;i++)
        cout << d[1][0][i] << ' ';*/

    int res1 = 0;
    long long res2 = 0ll;
    while(Q--) {
        int a,b;fin>>a>>b;
        int m = inf;
        for (int i=0;i<k;i++)
            m = min(m, d[1][i][a] + d[0][i][b]);

        if (m != inf)
            res1++, res2 += m;
    }
    fout << res1 << '\n';
    fout << res2 << '\n';

    return 0;
}