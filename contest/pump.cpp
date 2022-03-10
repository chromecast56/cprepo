#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int n,m;
struct edge
{
    int a,b,fl,co;
    bool operator<(const edge &a) const {
        return fl > a.fl;
    }
};
vector<edge> G[1001];
int f[1001], c[1001];
int D[1001];
vector<edge> elist;

int res1 = 0, res2 = 1e9;
int res = 0;
int dijskra() //repeatedly do dijskra from 1 to n for min cost, while the flow monotonically increases (1e9 for no path)
{
    fill(D,D+1001,1e9);
    queue<int> q;
    D[1] = 0;
    q.push(1);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for (int i=0;i<G[cur].size();i++)
            if (G[cur][i].fl >= res1) {     //if edge isn't removed
                int to = G[cur][i].b;
                int co = G[cur][i].co;
                if (D[to] > D[cur]+co)
                    D[to] = D[cur]+co,
                    q.push(to);
            }
    }
    return D[n];
}
int main()
{
    ofstream fout("pump.out");
    ifstream fin("pump.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    fin>>n>>m;

    for (int i=0;i<m;i++) {
        int a,b,co,fl;
        fin>>a>>b>>co>>fl;
        G[a].pb({a,b,fl,co});
        G[b].pb({b,a,fl,co});

        elist.pb({a,b,fl,co});
    }
    sort(elist.begin(),elist.end());

    while(1) {
        res1 = elist.back().fl; //res1 is lower bound for flow in system
        res2 = dijskra();
        if (res2 == 1e9) break;

        while(elist.back().fl == res1) elist.pop_back();

        res = max(res,(int) floor(1000000*1.0*res1/res2));
    }


    fout << res << '\n';
    return 0;
}