/*
                Change a[ind+1]
                results in prefix
                nice

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

set<int> s;
string c = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        vi a(n);
        vector<int> res(n+1);
        cout << c;
        for (int i=0;i<n;i++) {
            cin>>a[i];

            char b = c[a[i]];
            if (b=='z')b='a';else b++;

            c[a[i]] = b;
            cout << c;
        }


    }



    return 0;
}