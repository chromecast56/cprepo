/*
                    We have a data structure that can:
                        Insert points (x,y) (make a[x][y] = 1)
                        Delete points (x,y) (make a[x][y] = 0)

                        Query for the sum from (1,1) to (x,y) (from 1,1, not 0,0)

                        Note that this is a compressed DS
                        Each query = log^2(n)


                    Here we apply this data structure to an online inversion count problem with point updates

                    Say that the points are on the 2D plane, points (i,a[i]).
                    When we remove the point (i,a[i]), all points in the 2nd quadrant relative to (i.a[i]) (-x,+y)
                    get -1 to their contribution to inversion count, same with the 4th quadrant

                    (Think of it as all inversion pairs that contain index i are removed (i,x),(x,i))
                    Likewise, when we add a point (i,a[i]), the same set of points gets contribution +1

                    So we can maintain a cummulative answer and update it with each removal/addition



                    How does the DS work?
                    For every x-g(i), you store a set. (store an array of sets)
                    When updating, you either insert, or remove points (x,y) from every x-g(i)

                    When querying, you go through every x-g(i), and for each one find how many points have y-value <= y...
                    This can be done using order_of_key(x,y) in the OST

                    Generalized BIT
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
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}
// src: https://codeforces.com/blog/entry/52094
//To do it with larger values (>1e5), instead of keeping an array of OSTs, we can keep a hashmap
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