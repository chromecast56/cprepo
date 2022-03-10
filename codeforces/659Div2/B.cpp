/*
                        There are some safe spots where no matter what we wont drown (a[i]+k <= l)
                        Here we will "recharge" until wave = k

                        Between safe spots are unsafe spots. While the wave is going down, we want to go to the next unsafe spot
                        as fast as possible (wait until a[i]+k <= l), then go. If the wave is going up, we have to pray that

                        we can make it each time and that we wont drown. If at any time during upwave we will drown if we move, then we
                        will eventually drown (have to wait wave up to k then down, but we cant bc we are on unsafe spot)
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
const int MX = 4e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

string c = "abcdefghijklmnopqrst";
int a[MX];
int p[MX];
int n,l,k;
bool solve(int l,int r) {

}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        cin>>n>>k>>l;
        for (int i=0;i<n;i++)cin>>a[i];

        for (int i=0;i<n;i++) a[i]=l-a[i];
        bool b=1; int max_d = k;
        int dir = -1;
        for(int i=0;i<n;i++) {
            if (a[i] >= k) max_d = k, dir=-1;

            if (a[i]<0) b=0;

            if (dir==-1) {
                max_d = min(max_d,a[i]); //minimum of max depth allowed
            }
            else {
                if (a[i] < max_d) b=0; //if cant be increasing
            }

            if (!max_d) dir = 1;
            if (max_d==k) dir=-1;
            max_d += dir;
        }
        cout << (b? "Yes\n":"No\n");
    }

    return 0;
}