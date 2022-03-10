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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

int f[2][100000]; //f = amount a using first i b (hc), or amount a using last i b (lc)
int f2[2][100000]; // f2 = max wins using subset [0,i] of both a and b
int main()
{
 //   ofstream fout("cardgame.out");
  //  ifstream fin("cardgame.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;cin>>n;
    vi a(n),b;
    vi v(2*n+1);
    for (int i=0;i<n;i++) cin>>a[i], v[a[i]] = 1;
    for (int i=1;i<=2*n;i++) if (!v[i]) b.pb(i);

    sort(rall(a)); sort(rall(b));

    int itr = 0;
    for (int i=0;i<n;i++) {
        while(itr<n&&a[itr]>b[i]) itr++;
        if (itr<n) f[0][i] = itr;
        else f[0][i] = -1;
        itr++;
    }
    for (int i=0;i<n;i++)
        if (f[0][i] != -1)
            f2[0][f[0][i]] = i+1;

    for (int i=1;i<n;i++) f2[0][i] = max(f2[0][i],f2[0][i-1]);
    itr = n-1;
    for (int i=n-1;i>=0;i--) {
        while(itr>=0&&a[itr]<b[i]) itr--;
        if (itr>=0) f[1][i] = itr;
        else f[1][i] = -1;
        itr--;
    }
    for (int i=n-1;i>=0;i--)
        if (f[1][i] != -1)
            f2[1][f[1][i]] = n-i;

    for (int i=n-1;i>=0;i--) f2[1][i] = max(f2[1][i],f2[1][i+1]);


    int res = 0;
    for (int i=0;i<n;i++) res = max(res,f2[0][i]+f2[1][i+1]);
    res = max(res,f2[1][0]);
    cout << res << '\n';


    return 0;
}