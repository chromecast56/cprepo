/*
                    Classic knapsack dp after a reduction


                    Permutations.... Check for max/min stuff
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
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        vi a(2*n);
        for (int i=0;i<2*n;i++) cin>>a[i];

        vi sz;
        vi f(2*n+1);
        for (int i=2*n;i>=0;i--) {
            auto ind = find(a.begin(),a.end(),i);
            if (ind != a.end()) {
                int itr = 0;
                while(ind != a.end()) a.erase(ind), itr++;
                sz.pb(itr);
            }
        }

        f[0] = 1;
        for (auto s: sz) {
            for (int i=2*n;i>=0;i--)
                if (f[i] && i+s<=2*n) f[i+s] = 1;
        }

        cout << (f[n]? "Yes\n":"No\n");
    }

    return 0;
}