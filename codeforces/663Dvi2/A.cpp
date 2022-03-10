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

char a[200][200];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    while(t--) {
        int n;cin>>n;
        vl fact(n+1);
        vl p2(n+1);
        fact[0] = 1;
        p2[0] = 1;
        for (int i=1;i<=n;i++)
            fact[i] = (fact[i-1]*i) % MOD,
            p2[i] = (p2[i-1]*2) % MOD;

        /*
                        Read the fucking question clearly like wtf you literally misinterpreted it and got wrong answers
                        The question wants a[j] to be GREATER THAN a[i] for both sides...

                        Now it is very easy, bc if at any point a[j] > a[i], a[k] > a[i] for j<i<k, then it is cyclic
                        Complementary counting count all (n!) - no cycles.
                        No cycles means its like a mountain w/ single peak. Store all in stack (n..1), place n, then try
                        each on either side. = 2^(n-1)

                        = n! - 2^(n-1)
         */


        cout << (fact[n] - p2[n-1] + MOD)%MOD << '\n';
    }

    return 0;
}