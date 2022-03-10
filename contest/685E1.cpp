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
int xr[100000];
int res[100000];
int main()
{
    setIO();

    int n;cin>>n;
    for (int i=2;i<=n;i++) {
        cout << "XOR " << 1 << ' ' << i << '\n'; cout.flush(); cin >> xr[i];
    }

    int a12, a13, a23;
    cout << "AND 1 2\n"; cout.flush(); cin >> a12;
    cout << "AND 1 3\n"; cout.flush(); cin >> a13;
    cout << "AND 2 3\n"; cout.flush(); cin >> a23;
    int x = xr[2] + 2*a12;
    int y = xr[3] + 2*a13;
    int z = (xr[2]^xr[3]) + 2*a23; //XOR OPERATION LOWER PRECEDENCE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    assert((x+y-z)%2 == 0);
    res[1] = (x+y-z)/2;
    for(int i=2; i <= n; i++)
        res[i] = (xr[i] ^ res[1]);
    cout << "! ";
    for(int i = 1; i <= n; i++)
        cout << res[i] << " ";
    cout << endl;
    cout.flush();
}