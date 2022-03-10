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
}/*
            Just imagine k+1 stacks. When you defeat a boss, add the "score" of some stack to res, and insert the boss value
            Notice that the score is simply the sum of values in the stack. In fact, we can "compress" the info in each
            stack to just a value. Notice that it is always optimal to "play" the stack with highest score, assuming
            decreasing sort.

            My intuition meandered, but got to the right answer. Basically, I noticed that it is always optimal to push
            on the first stack until the net score is less than 0, then find an algorithm for the negative values.

            I then generalized this intuition for the final solution, which is implemented with a priority queue.
 */
int main()
{
    setIO();
    priority_queue<ll> pq;
    int n,k;cin>>n>>k;

    for (int i=0;i<=k;i++) pq.push(0);
    vl a;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        a.pb(x);
    }
    sort(all(a));
    ll res = 0;
    for (int i=n-1;i>=0;i--) {
        ll x = pq.top(); pq.pop();
        res += x;
        x += a[i];
        pq.push(x);
    }
    cout << res << '\n';

    return 0;
}
