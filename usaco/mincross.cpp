/*
            Basically, find out that for top row a[i] = 0 to n-2, the number of intersections is invariant.
            Only switches when looping over.
            In fact, when looping over, say i is the index of its respective edge leading to the bottom row.
            Since the top index is always at the end (n-1), you lose n-i-1 intersections, and gain i intersections...
            net change = 2i-n-1.

            And initial is the number of inversions after looking closely.
            DO NOTE: Have to try moving top row, and also try moving bottom row because as you can see, the system
            isn't symmetrical
            
            This is a nice bug checking idea - If you only have some WA, try seeing if you forgot to iterate on
            something you took for granted.
 */

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

struct BIT {
    static const ll MAXN = 100100;
    ll BT[MAXN+2];
    ll get(ll ind) {
        ll sum = 0;
        ind++;
        while (ind>0) {
            sum += BT[ind];
            ind -= ind & (-ind);
        }
        return sum;
    }
    void add(ll ind, ll val) {
        ind++;
        while (ind <= MAXN) {
            BT[ind] += val;
            ind += ind & (-ind);
        }
    }
};
BIT bit;
int main()
{
    ofstream fout("mincross.out");
    ifstream fin("mincross.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vl a,b;
    int n;fin>>n;
    vi index(n), arr(n);
    for (int i=0;i<n;i++) {int x;fin>>x;a.pb(x);index[a[i]]=i;}
    for (int i=0;i<n;i++) {int x;fin>>x;b.pb(x);arr[index[b[i]]] = i;}

    ll d=0, min_d = 0, inv = 0;
    for (int i=0;i<n;i++)
        inv += bit.get(100000) - bit.get(arr[i]),
        bit.add(arr[i],1);

    //shift bottom row
    for (int i=n-1;i>=0;i--)
        d -= (n-index[b[i]]-1) - index[b[i]],
        min_d = min(min_d,d);

    //try shifting top row
    d=0;
    for (int i=0;i<n;i++) index[b[i]] = i;
    for (int i=n-1;i>=0;i--)
        d -= (n-index[a[i]]-1) - index[a[i]],
        min_d = min(min_d,d);

    fout << inv+min_d << '\n';
    return 0;
}