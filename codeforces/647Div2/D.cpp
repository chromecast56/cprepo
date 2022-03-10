#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

vi G[1000000];
vector<pii> ord; // (val,ind)
int val[1000000];
int res[1000000];
unordered_set<int> s;
bool test(pii x) {
    s.clear();
    for (auto v: G[x.S])
        s.insert(val[v]);

    if (s.find(x.F) != s.end()) return 0; //if we already have val
    for (int i=1;i<x.F;i++)
        if (s.find(i) == s.end())     //need all vals [1,x) in order to put in x
            return 0;

    return 1;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,m;
    cin>>n>>m;
    while(m--) {
        int a,b;
        cin>>a>>b;
        G[a].pb(b);
        G[b].pb(a);
    }

    for (int i=1;i<=n;i++) {
        int x; cin>>x;
        ord.pb({x,i});
    }

    bool b = 1;
    sort(ord.begin(),ord.end());
    for (int i=0;i<n;i++)
        if (test(ord[i]))
            val[ord[i].S] = ord[i].F;
        else {
            b = 0; break;
        }

    if (!b) cout << "-1\n";
    else {
        for (auto v: ord)
            cout << v.S << ' ';
    }
    cout << endl;

    return 0;
}