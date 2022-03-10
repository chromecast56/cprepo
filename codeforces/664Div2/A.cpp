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
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

int n,m;
int x,y;
void solve(int r,bool b) {
    if (b) {
        cout << x << ' ' << y << '\n';
        for (int i=1;i<=m;i++)
            if (i != y)
                cout << x << ' ' << i << '\n';
        y = m;
    }
    else {
        if (y==m) {
            for (int i = m; i >= 1; i--)
                cout << r << ' ' << i << '\n';
            y = 1;
        }
        else {
            for (int i=1;i<=m;i++)
                cout << r << ' ' << i << '\n';
            y = m;
        }
    }
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    cin>>x>>y;

    solve(x,1);
    for (int i=1;i<=n;i++)
        if (i != x)
            solve(i,0);

    return 0;
}