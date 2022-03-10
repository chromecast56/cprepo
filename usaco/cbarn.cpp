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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}
const int MAXN = 1010, MAXK = 10;
ll f[MAXK][MAXN], w[MAXN][MAXN]; //store weight function
int n,k;
vl a;
void dc(int l,int r,int kk,int offset, int tl=0,int tr=n-1) {
    if (tl>tr) return;
    int tm = (tl+tr)/2;

    pll opt = {LONG_LONG_MAX,l}; //F = optimal value, S = index of optimal value - range [max(tl,l),min(tr,r)]
    //next time don't mess with the for loop code, as you want i to iterate over all of l to r (stupid)
    for (int i=l;i<=min(tm,r);i++)
        opt = min(opt, {f[kk-1][i]+w[(offset+i+1)%n][(offset+tm)%n], i});

    f[kk][tm] = min(f[kk-1][tm], opt.F);
    dc(l,opt.S,kk,offset,tl,tm-1);
    dc(opt.S,r,kk,offset,tm+1,tr);
}
ll solve(int offset) { //line case, if structure is array, cows only move left.
    memset(f,0,sizeof(f));

    //set base case: 1 door which has to be at index 0
    for (int i=0;i<n;i++)
        f[0][i] = w[offset][(offset+i)%n];

    for (int i=1;i<k;i++)
        dc(0,n-1,i,offset);
    return f[k-1][n-1];
}
int main()
{
    ofstream fout("cbarn.out");
    ifstream fin("cbarn.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>k;
    for (int i=0;i<n;i++) {int x;fin>>x;a.pb(x);}
    for (int i=0;i<n;i++) a.pb(a[i]); //circle it

    //precompute weight function
    for (int i=0;i<n;i++) {
        ll cost=0;
        for (int j=i+1;j<i+n;j++)
           cost += a[j%n]*(j-i), w[i][j%n] = cost;
    }

    ll res = LONG_LONG_MAX;
    for (int i=0;i<n;i++)
        res = min(res,solve(i)); //solve with an offset of i


    fout << res << '\n';

    return 0;
}