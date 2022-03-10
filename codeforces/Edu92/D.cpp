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
        ll n,k;cin>>n>>k;
        pair<ll,ll> a,b;cin>>a.F>>a.S>>b.F>>b.S;
        if (a>b) swap(a,b);
        pair<ll,ll> c = {min(a.F,b.F),max(a.S,b.S)};

        ll res = 0; ll cur = 0;
        ll make_all = (2*(c.S-c.F)-(a.S-a.F)-(b.S-b.F)); //cost to make the segments touch

        if ((c.S-c.F)*n <= k) { //extend all no matter what
            res += make_all*n;
            cur += n*(c.S-c.F);

            int dif = k-cur;
            res+= dif*2;
            cout << res << '\n';
        }
        else if (a.S >= b.F) { //there is intersection, meaning we can increase by 1 in 1 step (not 2)
            int intr = min(a.S,b.S) - b.F;
            if (intr*n >= k) {
                cout << "0\n";
                continue;
            }
            else
                cout << k-intr*n << '\n';
        }
        else {
            int num_use = k/(c.S-c.F);
            res += num_use*make_all;
            cur += num_use*(c.S-c.F);

            int leftover = k-cur;
            if (!leftover)
                cout << res << '\n';
            else {
                ll c1 = b.F-a.S + (k-cur); //case 1: go to the next seg but dont fully finish

                ll c2;  //case 2: build on a seg. If we dont have existing seg, it is always best to do c1 (as wed have to extend for them to touch, but c1 is 1 and c2 is 2 per)
                if (num_use == 0)
                    c2 = INT_MAX;
                else
                    c2 = 2*(k-cur);

                cout << res +min(c1,c2) << '\n';
            }
        }

    }

    return 0;
}