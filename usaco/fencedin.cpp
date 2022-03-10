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

/*
            Motivation: Obviously this is a simple MST problem, but the time complexity of O(nm) (nm verticies) is too big
            We have to exploit the patterns presented in the grid  -Theres a reason why it is in a grid instead of a
            general graph.

            In regular Kruskal MST, you greedily select the smallest edges.
            Here, the smallest edges are in batches of rows/cols, with n+m total batches

            If we can speed the algo up by processing batches (linear) instead of individual cells (quadratic), we win
            And we can. Call row,col the number of row and col batches we have already processed.

            So first process batches by increasing size:
            Case 1: row=0 or col=0. By drawing the (very strong <3) test case, we can see that if we havent used
            any rows or any cols, we process the entire batch (size n/m, add n/m*length to res)

            Case 2: row!=0 and col!=0. This means that we don't use the entire batch (case row=1 or col=1 you do, but it is satisfied)
            Say we're processing a row. If we have already processed col columns, then the row we already processed has already
            merged the col columns, meaning we don't have to use col-1 edges. This means we only use m-(col-1) edges in the batch
            Likewise, if we're processing a col, we only use n-(row-1) edges in the batch.

            You see how row=1 and col=1 are satisfied?
 */
int main()
{
    ofstream fout("fencedin.out");
    ifstream fin("fencedin.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int A,B,n,m;fin>>A>>B>>n>>m;
    vl a(n), b(m);
    vpll tot;
    a.pb(0), b.pb(0);
    for (int i=0;i<n;i++) fin>>a[i]; a.pb(A);
    for (int i=0;i<m;i++) fin>>b[i]; b.pb(B);
    sort(all(a)); sort(all(b));

    for (int i=0;i<sz(a)-1;i++)
        tot.pb({a[i+1]-a[i],0});
    for (int i=0;i<sz(b)-1;i++)
        tot.pb({b[i+1]-b[i],1});

    sort(all(tot));
    int eleft = n*m+n+m; int row=0,col=0; //number of rows/cols we used
    ll res = 0;
    for (auto e: tot) {
        if (!e.S) { //on row
            if (!row || !col) eleft -= m, res += e.F*m;
            else eleft -= m - (col-1), res += e.F*(m-(col-1));
            row++;
        }
        else { //on col
            if (!row || !col) eleft -= n, res += e.F*n;
            else eleft -= n - (row-1), res += e.F*(n-(row-1));
            col++;
        }
        if (!eleft) break;
    }

    fout << res << '\n';

    return 0;
}