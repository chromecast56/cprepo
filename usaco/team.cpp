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
const int MOD = 1e9+9; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

int n,m,k;
ll a[1010],b[1010];
ll f[1010][1010][11];
/*
        Brute force dp: f[i][j][k] = sum of f[i'][j'][k-1]
        f[i][j][k] = sum of sets of k size, [0,i] in a and [0,j] in b
        Note that if you have a set of size k-1, if you add a[i] and b[j] st. a[i]>b[j], it is 1/1 and valid set of size k

        This is O(n^2m^2k), and you can just 2d prefix sum to speed up to O(nmk).
 */
int main()
{
    ofstream fout("team.out");
    ifstream fin("team.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>m>>k;
    for (int i=1;i<=n;i++) fin>>a[i];
    for (int i=1;i<=m;i++) fin>>b[i];

    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++) {
            if (a[i] > b[j])
                f[i][j][1] = 1;
            f[i][j][1] += f[i-1][j][1] + f[i][j-1][1] - f[i-1][j-1][1];
        }

    for (int kk=2;kk<=k;kk++) { //O(nm) speedup by 2d prefix sums
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++) {
                if (a[i]>b[j])
                    f[i][j][kk] = (f[i][j][kk] + f[i-1][j-1][kk-1])%MOD;
            }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                f[i][j][kk] = (f[i][j][kk] + f[i-1][j][kk] + f[i][j-1][kk] - f[i-1][j-1][kk])%MOD,
                f[i][j][kk] = (f[i][j][kk]+MOD)%MOD;
    }

    fout << f[n][m][k] << '\n';

    return 0;
}