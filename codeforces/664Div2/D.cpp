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


int main() {
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, d, m;
    cin >> n >> d >> m;
    vl a(n), b(n); //a = mad, b = not

    ll bcnt = 0;
    ll sum = 0;
    a.pb(0);b.pb(0);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sum += x;
        bcnt += x > m;
        if (x > m) a.pb(x); else b.pb(x);
    }


    sort(a.begin()+1,a.end(),greater<>());

    sort(b.begin()+1,b.end(),greater<>());
    for (int i = 1; i < sz(a); i++) a[i] += a[i - 1];
    for (int i = 1; i < sz(b); i++) b[i] += b[i - 1];

    ll res = 0;
    /*for (int i=1;i<=bcnt;i++) {//loop on # bad... the bad elements will take up (i-1)*(d+1)+1 days
        int t = n-(i-1)*(d+1)-1;
        if (t > 0 && t <= sz(b))
            res = max(res,a[i-1]+b[t-1]);
    }*/
    for (int i=0;i<=n;i++) { //loop number of good group
        int rem = n-i;
        int numb = (rem+d)/(d+1);
        res = max(res,a[numb]+b[i]);
    }

    cout << res << '\n';

    return 0;
}