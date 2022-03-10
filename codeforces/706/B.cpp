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
/*
            Key idea is that this is just a casework bash. Imagine it is a mountain, going up and down with local mins and maxes.

            Idea 1: You cannot start on a "slope" since you can only go down one way - he places right below you.
            This restricts you to only be at local maxes, where you can go two ways.

            Idea 2: Notice that if he wants to beat you, the initial run length distance must be odd.
            Say that theres a peak, run length to the left is a, and run length to the right is b.
            He obviously wants to place in the larger of a,b. If he doesn't, then you go to larger, and then you have more space.
            WLOG a is larger, but he has to place on a-1 if even (and on a if odd).
            This means that all of form (2n,2n) you win.

            But if theres multiple, then he goes to another region and he wins. So you must account for that.


 */
int main()
{
    setIO();
    vi v,cv,a;
    int n;cin>>n;
    for (int i=0;i<n;i++) {
        int x;cin>>x;a.pb(x);
        if (i) {
            if (a[i]>a[i-1]) v.pb(1); else v.pb(0);
        }
    }
    int b = v[0]; cv.pb(1);
    for (int i=1;i<sz(v);i++) {
        if (v[i]==v[i-1]) cv.back()++;
        else cv.pb(1);
    }

    //for (auto x: cv) cout << x << ' ';
    int mx=0,mx_f = 1;
    for (auto x: cv)
        if (mx==x) mx_f++;
        else if (mx < x) mx = x, mx_f = 1;

    int test = 0;
    for (int i=2-b;i<sz(cv);i+=2) {
        if (cv[i]==cv[i-1] && cv[i]==mx && cv[i]%2==0) {
            test = 1;
        }
    }

    if (mx_f == 2 && test) {
        cout << "1\n";
    }
    else {
        cout << "0\n";
    }
    return 0;
}
//REMEMBER TO DELETE UNUSED BEFORE SUBMITING - NO templates allowed


