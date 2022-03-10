#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

const int N = 200100;
ll a[N],b[N],c[N];
pii e[N]; //the number of switches (0/1, 1/0 to do at this node, starts at 1 for everything and we waterfall up ())
vi G[N];
void dfs(int cur, int p = 0) {
    a[cur] = min(a[cur],a[p]); //transition a[i] from cost to minimum cost
    for (auto next: G[cur]) if (next != p)
        dfs(next,cur);

    //back propagation
    int delta = e[cur].F - e[cur].S; //amount left over
    if (delta > 0)  //more 0/1
        e[p].F += delta, e[cur].F -= delta;
    else if (delta < 0)
        e[p].S -= delta, e[cur].S += delta;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];
    for (int i=0;i<n-1;i++) {
        int u,v; cin>>u>>v;
        G[u].pb(v);
        G[v].pb(u);
    }

    for (int i=1;i<=n;i++)
        if (!b[i] && c[i]) e[i].F++;
        else if (b[i] && !c[i]) e[i].S++;

    a[0] = INT_MAX;
    dfs(1);

    ll res = 0;
    for (int i=1;i<=n;i++) {
        assert(e[i].F == e[i].S);
        res += 2*a[i]*e[i].F;               //pairing costs 2x
    }

    if (e[0].F != 0 || e[0].S != 0)  //cannot pair everything
        cout << "-1\n";
    else
        cout << res << '\n';

    return 0;
}