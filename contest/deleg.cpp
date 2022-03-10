#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;

const int maxn = 100100;
int n;
vi G[maxn];
int p[maxn]; //parents where 1 is root
int v[maxn];

vi tsort; //topological sorting of nodes (preorder traversal)
void dfs(int cur) {
    v[cur] = 1;
    tsort.pb(cur);
    for (auto ne: G[cur])
        if (!v[ne])
            p[ne]=cur, dfs(ne);
}
void toposort() {
    dfs(1);
    reverse(tsort.begin(),tsort.end());
}

int works(int k,int cur = 1) { //for given k and node, try to partition into edge-sets of k, return remaining edges
    unordered_multiset<int> s;
    v[cur] = 1;
    for (auto ne: G[cur])
        if (!v[ne]) {
            int w = works(k,ne);
            if (w == -1) return -1;
            s.insert(w);
        }

    unordered_multiset<int> t;
    for (auto val: t)
        if (val==k) s.erase(val);
        else if (s.find(k-val) != s.end())
            s.erase(val);

    if (s.size() > 1) return -1;
    if (s.size() == 1) return *s.begin();
    return 1;
}
int main()
{
//    ofstream fout("deleg.out");
//    ifstream fin("deleg.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n;
    for (int i=0;i<n-1;i++) {
        int a,b;
        cin>>a>>b;
        G[a].pb(b);
        G[b].pb(a);
    }

    toposort();

    for (int i=1;i<=n;i++)
        if ((n-1) % i == 0) {//can only if evenly divides n
            memset(v,0,sizeof(v));
            cout << (works(i) == -1 ? '0' : '1');
        }
        else cout << '0';

    cout << '\n';
    return 0;
}