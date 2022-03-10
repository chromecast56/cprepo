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
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

vpii out[MX], in[MX];
int n,m,k;
int mem[10][10][10][10]; //= 1 if pairs of pairs CANNOT be together
int mem2[10][10]; //for edges that have duplicates ingoing...
ll res = 0;
vi cur;
bool check() {
    for (int i=0;i<k;i++)
        for (int j=i;j<k;j++)
            if (mem[cur[i]][i+1][cur[j]][j+1] || mem2[cur[i]][i+1] || mem2[cur[j]][j+1])
                return 0;
    return 1;
}
void gen(int ind) {
    if (ind==k+1) {
        if (check())
            res++;
        return;
    }
    for (int i=1;i<=ind;i++) {
        cur.pb(i);
        gen(ind+1);
        cur.pop_back();
    }
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for (int i=0;i<m;i++) {
        int u,v,w;cin>>u>>v>>w;
        out[u].pb({w,v});
    }

    for (int i=0;i<MX;i++) {
        sort(out[i].begin(),out[i].end());

        for (int j=0;j<sz(out[i]);j++)
            in[out[i][j].S].pb({j+1,sz(out[i])});
    }


    for (int i=0;i<MX;i++) {
        bool b = 0; //duplicates?
        sort(in[i].begin(),in[i].end());
        for (int j=1;j<sz(in[i]);j++)
            if (in[i][j] == in[i][j-1]) { //for all duplicates, they are just bad (at least 2 ingoing), use another cache
                pii x = in[i][j];
                mem2[x.F][x.S] = 1;
            }

        in[i].erase(unique(in[i].begin(),in[i].end()), in[i].end()); //now, guarenteed that sz(in) <= 81

        for (int a=0;a<sz(in[i]);a++)
            for (int b=0;b<sz(in[i]);b++)
                if (a!=b) {
                    pii x = in[i][a], y = in[i][b];
                    mem[x.F][x.S][y.F][y.S] = 1;
                }
    }



    gen(1);
    cout << res << '\n';

    return 0;
}
