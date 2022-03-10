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
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index
template <class T> using Tree = tree<T, null_type, greater<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

/*
            Like regular BIT, except instead of an array we use a hashmap so we can do operations on larger values (keep in mind ll)
 */
struct BIT {
    static const ll MAXN = 1e9+2;
    unordered_map<ll,ll> BT;
    ll get(ll ind) {
        ll sum = 0;
        ind++;
        while (ind>0) {
            sum += BT[ind];
            ind -= ind & (-ind);
        }
        return sum;
    }
    ll sum(ll l,ll r) {
        return get(r) - get(l-1);
    }
    void add(ll ind, ll val) {
        ind++;
        while (ind <= MAXN) {
            BT[ind] += val;
            ind += ind & (-ind);
        }
    }
};
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    return 0;
}