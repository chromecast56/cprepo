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
int MSB(int x) {
    for (int i=31;i>=0;i--)
        if (x&(1<<i))
            return i;
}
int s[32];
int main()
{
    setIO();
    int n;cin>>n;
    vi a,b;
    for (int i=0;i<n;i++) {
        int x;cin>>x; int msb = MSB(x);
        a.pb(x); b.pb(msb);
        s[msb]++;
    }
    //pidgonhole
    for (int i=0;i<32;i++) if (s[i] > 2) {
            cout << 1 << '\n';
            return 0;
        }

    //test if merging inbetween works
    for (int i=1;i<sz(a)-1;i++)
        if (b[i]==b[i+1] && (a[i]^a[i+1]) < a[i-1]) {
            cout << 1 << '\n';
            return 0;
        }

    //now brute force
    int res = 1000;
    for (int i=0;i<sz(a)-1;i++) {
        int xor1=0,xor2=0;
        for (int l=i;l>=0;l--) {
            xor1 ^= a[l];
            xor2=0;
            for (int r=i+1;r<sz(a);r++) {
                xor2 ^= a[r];
                if (xor1>xor2)
                    res = min(res,r-l-1);
            }
        }
    }
    cout << (res==1000?-1:res) << '\n';

    return 0;
}