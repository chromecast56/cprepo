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

int f[200][200]; //f(i,j) = from point i,j, the farthest right you can go until reaching swamp
int n,m;
char a[200][200];
int main()
{
    ofstream fout("fortmoo.out");
    ifstream fin("fortmoo.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fin>>n>>m;
    for (int i=0;i<n;i++) {
        string x;fin>>x;
        for (int j=0;j<m;j++) a[i][j] = x[j];
    }

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++) {
            int itr = j;
            while(itr<m && a[i][itr]!='X') itr++;
            f[i][j] = itr;
        }

    int res = 0;
    for (int i=0;i<m;i++)
        for (int j=i+1;j<m;j++) {
            int ix=-1;
            for (int k=0;k<n;k++) {
                if (a[k][i]=='X' || a[k][j]=='X')
                    ix = -1;
                if (f[k][i] > j) { //found suitable rectangle
                    if (ix==-1) ix = k;
                    res = max(res,(j-i+1)*(k-ix+1));
                }
            }
        }

    fout << res << '\n';

    return 0;
}