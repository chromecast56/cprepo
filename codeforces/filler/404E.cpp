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
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

struct bit2D {
    static const int N = 200100;
    Tree<pii> bit[N];

    void insert(int x, int y) {
        for(int i = x; i < N; i += i & -i)
            bit[i].insert({y, x});
    }
    void remove(int x, int y) {
        for(int i = x; i < N; i += i & -i)
            bit[i].erase({y, x});
    }
    int query(int x, int y) {
        int ans = 0;
        for(int i = x; i > 0; i -= i & -i)
            ans += bit[i].order_of_key({y+1, 0});
        return ans;
    }
};
ll res = 0;
bit2D b;
void remove(int x,int y) {
    int q2 = b.query(x-1,200000) - b.query(x-1,y);
    int q4 = b.query(200000,y-1) - b.query(x,y-1);

    res -= q2+q4;
    b.remove(x,y);
}
void insert(int x,int y) {
    int q2 = b.query(x-1,200000) - b.query(x-1,y);
    int q4 = b.query(200000,y-1) - b.query(x,y-1);

    res += q2+q4;
    b.insert(x,y);
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q;cin>>n>>q;
    vi a(n+1);
    for (int i=1;i<=n;i++) {
        a[i] = i;
        insert(i,a[i]);
    }

    while(q--) {
        int l,r;cin>>l>>r;
        remove(l,a[l]); remove(r,a[r]);
        swap(a[l],a[r]);
        insert(l,a[l]); insert(r,a[r]);

        cout << res << '\n';
    }


    return 0;
}