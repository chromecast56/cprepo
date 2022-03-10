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


int main()          //bugs to worry about next time::::::: OFF BY ONE!!! I even remembered that push backs could inclued going all the way, but just blanked out
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n,k,z;cin>>n>>k>>z;
        k++;
        vector<ll> a(n);
        for (int i=0;i<n;i++) cin>>a[i];
        ll res=0;
        for (int itr=0;itr<=z;itr++) {
            ll sum=0;
            int kk = k-2*itr;
            vi b;
            for (int i=min(n-1,kk);i>=1;i--) if (i != n) b.pb(a[i]+a[i-1]);
            for (int i=0;i<kk;i++) sum += a[i];
            sort(b.rbegin(),b.rend());
            if (sz(b)) sum += b[0]*itr;

            res = max(res,sum);
        }
        cout << res << '\n';
    }

    return 0;
}