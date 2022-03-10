/*
                        Typical interval dp:
                        Stage = interval length,
                        state = initial position


                        f[l...r] dp recurrence:

                            Case 0: l==r. There is 1 element, delete in 1 sec.
                                f[l][r] = 1

                            Case 1: a[l] == a[r]. This means that in f[l+1][r-1], when there is one second left, we take a[l] and a[r] with it
                                f[l][r] = f[l+1][r-1] iff a[l]==a[r]

                            Case 2: Typical dp on interval. Iterate over break point
                                f[l][r] = f[l][k] + f[k+1][r]
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
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
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

int f[1000][1000]; //store answer 1...n
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;cin>>n;
    vi a(n);

    for (int i=0;i<n;i++) cin>>a[i];

    for (int d=0;d<n;d++)
        for (int i=0;i+d<n;i++) {
            int j = i+d;
            if (d==0) f[i][j] = 1;
            else if (d==1 && a[i]==a[j]) f[i][j] = 1;
            else {
                int x = min(f[i][j-1],f[i+1][j]) + 1;
                if (a[i] == a[j])
                    x = min(x,f[i+1][j-1]);

                for (int k=i;k<j;k++)
                    x = min(x, f[i][k]+f[k+1][j]);

                f[i][j] = x;
            }
        }

    cout << f[0][n-1];

    return 0;
}