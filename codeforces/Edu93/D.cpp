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

ll f[201][201][201]; //call f the answer using i A, j B, k C
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int A,B,C; cin>>A>>B>>C;
    vl a(A+1),b(B+1),c(C+1);
    for (int i=1;i<=A;i++) cin>>a[i];
    for (int i=1;i<=B;i++) cin>>b[i];
    for (int i=1;i<=C;i++) cin>>c[i];

    sort(a.begin()+1,a.end(),greater<>());sort(b.begin()+1,b.end(),greater<>());sort(c.begin()+1,c.end(),greater<>());
    ll res =0;


    for (int i=0;i<=A;i++)
        for (int j=0;j<=B;j++)
            for (int k=0;k<=C;k++) {
                if (!i||!j||!k) { //we dont use one
                    if (!i) {
                        if (j&&k) f[i][j][k] = f[i][j-1][k-1] + b[j]*c[k];
                    }
                    if (!j) {
                        if (i&&k) f[i][j][k] = f[i-1][j][k-1] + a[i]*c[k];
                    }
                    if (!k) {
                        if (i&&j) f[i][j][k] = f[i-1][j-1][k] + a[i]*b[j];
                    }
                }
                else
                    //we can use all
                    f[i][j][k] = max(max(f[i-1][j-1][k]+a[i]*b[j],f[i-1][j][k-1]+a[i]*c[k]), f[i][j-1][k-1]+b[j]*c[k]);

                res = max(res,f[i][j][k]);
            }

    cout << res << '\n';

    return 0;
}