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
#define lb lower_bound
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void setIO(string name = "") { // empty if stdin/out
    ios_base::sync_with_stdio(0); cin.tie(0); // make IO faster
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
struct point{
    ll x, y;

    friend bool operator<(point a, point b){
        if(a.x == b.x)
            return a.y < b.y;

        return a.x < b.x;
    }

    friend bool operator==(point a, point b){
        return a.x == b.x && b.y == a.y;
    }
    friend bool operator!=(point a, point b){
        return !(a == b);
    }
};

vector<point> A, B;
//cross product of vectors OA and OB        Positive for counterclockwise, negative for clockwise
long long cross(point &O,point &A,point &B)
{;
    return (A.x-O.x)*(B.y-O.y) - (B.x-O.x)*(A.y-O.y);
}
vector<point> convex_hull(vector<point> &v)
{
    sort(v.begin(),v.end());
    v.erase(unique(all(v)),v.end());

    int n = v.size(), k = 0;
    if(n == 1)
        return v;
    if(n == 2){

        if(v[0] == v[1])
            return {v[0]};
        return v;
    }
    if(n == 3){
        if(v[0] == v[1] && v[1] == v[2])
            return {v[0]};
        if(v[0] == v[1] )
            return {v[1], v[2]};
        if( v[1] == v[2])
            return {v[0], v[1]};
        if(cross(v[0], v[1], v[2])!=0) {
            if(cross(v[0], v[1], v[2])) reverse(all(v));
            return v;
        }
        return {v[0], v[2]};//colinear
    }

    vector<point> res(2*n);
    //build lower hull
    for (int i=0;i<n;i++)
    {
        while(k >= 2 && cross(res[k-2],res[k-1],v[i]) <= 0) //remove k-1 if it is a clockwise turn
            k--;
        res[k++] = v[i];
    }
    //build upper hull
    int t = k+1; //t represents all pts in lower hull and the  initial pt for upper
    for (int i=n-1;i>0;i--)
    {
        while(k >= t && cross(res[k-2],res[k-1],v[i-1]) <= 0) //remove k-1 if it is a clockwise turn
            k--;
        res[k++] = v[i-1];
    }
    res.resize(k-1); //resize

    return res;
}
int main()
{
    setIO();
    while(true){
        int n; cin >> n;
        if(n == 0) return 0;

        vector<point> points(n);

        for(int i =0; i< n;i++)
            cin >> points[i].x >> points[i].y;

        vector<point> ans  = convex_hull(points);
        cout << ans.size()<<endl;
        for(point p : ans)
            cout << p.x<<" "<<p.y<<endl;
    }

    return 0;
}



