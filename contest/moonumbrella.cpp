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
#define lb lower_bound
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
void ans() {
    int res = 0;
    int x,y;cin>>x>>y;
    string s; cin>>s; //CJ = x, JC = y;
    int n = sz(s);
    vector<char> a;
    for (int i=0;i<n;i++) a.pb(s[i]);

    for (int i=0;i<n-1;i++) {
        if (a[i]=='C' && a[i+1] == 'J') res += x;
        if (a[i]=='J' && a[i+1] == 'C') res += y;
    }

    while(!a.empty() && a[0] =='?') a.erase(a.begin());
    while(!a.empty() && a.back()=='?') a.pop_back();
    for (int i=sz(a)-1;i>0;i--) if (a[i] == '?' && a[i-1] == '?') a.erase(a.begin()+i);

    for (int i=0;i<sz(a);i++) {
        if (a[i]=='?') {
            assert(i != 0 && i != sz(a)-1);
            if (a[i-1] == 'C' && a[i+1] == 'J') res += x;
            if (a[i-1] == 'J' && a[i+1] == 'C') res += y;
        }
    }
    cout << res;
}
int main()
{
    setIO();
    int t;cin>>t;
    for (int i=1;i<=t;i++)
        cout << "Case #" << i << ": ",ans(),cout << "\n";
    return 0;
}
//REMEMBER TO DELETE UNUSED BEFORE SUBMITING - NO templates allowed


