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
const int maxn = 200100;


int stk[maxn]; //for each value store which stack its in (stacks by rep in dsu)
vi A[maxn]; //adjlist of values
int n,m;

//dsu code: Not used in this problem (as it has to be modified) but future reference
struct dsu {
    int p[maxn]{};
    int sz[maxn]{};
    dsu() {for (int i=0;i<maxn;i++)p[i]=i,sz[i]=1;}
    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }
    void merge(int u,int v) {
        u = find(u), v = find(v);
        if (u!=v) {
            if (sz[u]<sz[v]) swap(u,v);
            p[v]=u;
            sz[u]+=sz[v];
        }

    }
};
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n>>m;

    int res = n-1; //initial amount, take away for every (i,i+1) pair
    for (int i=1;i<=n;i++) {
        int x; cin>>x;
        stk[i] = x;
        if (stk[i-1] == stk[i])
            res--;
        A[x].pb(i);
    }

    dsu dsu;

    cout<<res<<endl;
    for (int i=0;i<m-1;i++) {
        int a,b; cin>>a>>b;
        a = dsu.find(a), b = dsu.find(b); //go to rep
        if (dsu.sz[a] < dsu.sz[b]) swap(a,b);   //want b to be smaller

        for (auto v: A[b]) {
            if (v>0 && stk[v-1] == a) res--;
            if (v<n && stk[v+1] == a) res--;
        }

        dsu.merge(a,b);
        for (auto v: A[b]) {
            stk[v] = a;
            A[a].pb(v);
        }

        cout << res << '\n';
    }

    return 0;
}