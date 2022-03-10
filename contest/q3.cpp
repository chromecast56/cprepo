#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
#define lb lower_bound
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;
struct cow {
    int ind;
    unordered_set<int> s;
};
int a[300000],b[300000];
int res[300000];
cow arr[110];

struct DSU {

    vi p,siz;
    void start(int n) {p.resize(n),siz.resize(n);for (int i=0;i<n;i++)p[i]=i,siz[i]=1;}
    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }
    int size(int u) {return siz[find(u)];}
    void merge(int u,int v) {
        u = find(u), v = find(v);
        if (u!=v) {
            if (siz[u]<siz[v]) swap(u,v);
            p[v]=u;
            siz[u]+=siz[v];
        }

    }
};
int main()
{
    int n,k,m;cin>>n>>k>>m;
    for (int i=0;i<k;i++) {
        cin>>a[i] >> b[i];
    }
    if (n <= 100 && k <= 200) {
        for (int i=1;i<=n;i++) arr[i].s.insert(i), arr[i].ind = i;
        for (int t=0;t<min(m,100000);t++) {
            int kk = t%k;
            swap(arr[a[kk]],arr[b[kk]]);
            arr[a[kk]].s.insert(a[kk]);
            arr[b[kk]].s.insert(b[kk]);
        }
        for (int i=1;i<=n;i++) res[arr[i].ind] = sz(arr[i].s);
        for (int i=1;i<=n;i++) {
            cout << res[i] << '\n';
        }
    }
    else {
        DSU dsu;
        dsu.start(300000);
        for (int i=0;i<k;i++) {
            dsu.merge(a[i],b[i]);
        }

        for (int i=1;i<=n;i++) {
            cout << dsu.size(i) << '\n';
        }
    }


    return 0;
}


