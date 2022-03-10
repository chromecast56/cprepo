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
int a[3][1100000];
int f[1100000][8]; //f i,msk
vi to[8];
int get(int ind) {
    return a[0][ind] + a[1][ind]*2 + a[2][ind]*4;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    if (n >= 4) { //have four 2x2 together which HAVE to be even, bad
        cout << "-1\n";
        return 0;
    }
    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    //now its a line of 2xm, or 3xm
    for (int i=0;i<n;i++)  {
        string x;cin>>x;
        for (int j=0;j<m;j++)
            a[i][j] = (x[j] == '1') ? 1:0;
    }

    /*
                    Basically...
                    4x4 squares cannot work
                    Assume that we modify to make it so that 2x2 squares are odd.
                    But 4x4 HAS to be even (4*odd)
                    So, any n >= 4 doesn't work

                    Now n < 4, and we only count 2x2 squares

                    if n==1, then we dont change anything

                    otherwise, we can do some bitmask dp
                    f[i][msk] --> f[i+1][nmsk] + delta(a[i+1],nmsk)
     */
    //to[i] will store all the bitmasks that can be reached from mask i (st the square condition holds)
    for (int i=0;i<(1<<n);i++)
        for (int j=0;j<(1<<n);j++) {
            bool b = 1;
            for (int k=0;k<n-1;k++) {
                int a1 = (i>>k)&1; int a2 = (j>>k)&1; int a3 = (i>>(k+1))&1; int a4 = (j>>(k+1))&1;
                if ((a1+a2+a3+a4)%2 == 0)
                    b = 0;
            }
            if (b)
                to[i].pb(j);
        }

    for (int i=0;i<m;i++) for (int j=0;j<(1<<n);j++) f[i][j] = INT_MAX;
    //f[i][msk] is the answer for [0...i] ending at mask msk
    int res = INT_MAX;
    for (int i=0;i<m-1;i++)
        for (int msk=0;msk<(1<<n);msk++) {
            if (i==0) {
                f[i][msk] = __builtin_popcount(get(i)^msk);
            }
            for (auto ne: to[msk])
                f[i+1][ne] = min(f[i+1][ne], f[i][msk] + __builtin_popcount(get(i+1)^ne));
        }

    for (int msk=0;msk<(1<<n);msk++)
        res = min(res,f[m-1][msk]);

    cout << res << '\n';

    return 0;
}