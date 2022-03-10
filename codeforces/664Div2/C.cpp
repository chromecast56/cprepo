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

int n,m;
int d[201][201];
int f[201][512];
vi G[201];
/*int dijsktra() {
    for (int i=0;i<n;i++) D[i][0] = d[i][0];
    for (int i=1;i<n;i++)
        for (int j=0;j<m;j++) {
            int min_d = MX;
            for (int k=0;k<m;k++)
                min_d = min(min_d, D[i-1][k] | d[i][j]);
            D[i][j] = min_d;
        }
    int res = MX;
    for (int i=0;i<m;i++) res = min(res,D[n-1][i]);
    return res;
}*/
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    vi a(n),b(m);
    for (int i=0;i<n;i++) cin>>a[i];
    for (int i=0;i<m;i++) cin>>b[i];

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            d[i][j] = a[i]&b[j];

    for (int i=0;i<m;i++) f[0][d[0][i]] = 1;
    //commented doesn't work because an optimal pt1 does not mean optimal pt2...
    //call f[i][x] = answer for [0...i] and works c|c|c|c = x

    //next time: just unlucky, initial worries were correct in that an optimal or doesn't necessarily lead to an optimal final solution
    for (int i=0;i<n-1;i++)
        for (int k=0;k<512;k++)
            if (f[i][k])
                for (int j=0;j<m;j++) {
                    int x = k|d[i+1][j];
                    f[i+1][x] = 1;
                }

    for (int i=0;i<512;i++)
        if (f[n-1][i]) {
            cout << i << '\n';
            return 0;
        }

    return 0;
}