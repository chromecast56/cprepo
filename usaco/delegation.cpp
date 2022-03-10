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
int n;
vi G[100100];
int solve(int k,int cur = 1,int par = -1) { //returns the size of the "stick" leaving node cur
    unordered_map<int,int> ch;
    for (auto ne: G[cur])
        if (ne != par) {
            int stk = solve(k,ne,cur);
            if (stk==-1) return -1;
            if (stk) { //pair sticks
                if (ch[k-stk]) ch[k-stk]--;
                else ch[stk]++;
            }
        }
    int numpy = 0, lone = 0;
    for (auto pa: ch) //find lone stick, but check if there still are multiple
        if (pa.S)
            numpy++, lone = pa.F;

    if (!numpy) return 1;                           //no stick, start one at 1
    if (numpy==1) return (lone+1)%k;   //existing stick, increase length and go to parent
    return -1;                                      //multiple sticks, impossible
}
int main()
{
    //setIO("deleg");
    cin>>n;
    for (int i=0;i<n-1;i++) {
        int a,b;
        cin>>a>>b;
        G[a].pb(b); G[b].pb(a);
    }

    cout << 1; //1 always good
    for (int k=2;k<=n-1;k++)
        if ((n-1)%k==0) cout << (solve(k)==1);
        else            cout << 0;

    cout << endl;

    return 0;
}
