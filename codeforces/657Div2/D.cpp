/*
                    Sweepline... Map everything to 0...m/2, and *2 to make it a circle.

                    Things to note: Instead of making it a circle, you could also make itr wrap around by modding it by m/2 when []
                    Look at what the output wants, because of my *2 implementation, my res2 could be off by m/2. At the very end,
                    convert my variables that work for me to the one that the colution wants
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
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
void sort(vector<t> &a) {sort(a.begin(),a.end());}

int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,h,m,k;cin>>n>>h>>m>>k;
    vector<pii> a; //store the minutes for each train. mapped onto 0-m/2, *2 for circularity
    for (int i=0;i<n;i++) {
        int hi,mi;cin>>hi>>mi;
        mi %= (m/2);
        a.pb({mi,i}); a.pb({mi+m/2,i});
    }

    sort(a);
    int itr=0;
    int res1=INT_MAX,res2=0;
    for (int init=0;init<2*n;init++) {
        while(itr<2*n && a[itr].F-a[init].F < k) itr++;
        if (itr==2*n) break;

        if (res1 > itr-init-1) res1=itr-init-1, res2 = a[itr].F;
    }

    cout << res1 << ' ' << res2 % (m/2) << '\n';

    for (int i=0;i<sz(a);i++)
        if (res2-k < a[i].F && a[i].F < res2)
            cout << a[i].S+1 << ' ';

    cout << endl;
    return 0;
}