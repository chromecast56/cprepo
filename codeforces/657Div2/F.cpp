#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
#define F first
#define S second
#define lb lower_bound
#define ub upper_bound
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

struct suffq {
    map<int,ll> m;
    void ins(int x,int y) { //insert (x,y), but we want to maintaint the invariant that if x_1<x_2<x_3... then y_1>y_2>y_3...
        auto it = m.lb(x); if (it!=m.end() && it->S >= y) return; //irrelevant
        it = m.insert(it,{x,y});
        it->S = y; //????
        while(it != m.begin() && prev(it)->S <= y) m.erase(prev(it));
    }
    int query(int x) { //query maximum y in the set st. the x val >= x... Because of our invariant we can simply do a lower_bound (y decreases)
        auto it = m.lb(x);
        if (it==m.end()) return 0; //x bigger than all m[i].x
        return it->S;
    }
};
vector<pii> Q;
int check(int ind) {
    suffq sf;
    for(int i=0;i<=ind;i++) if (!(Q[i].F&1))
        sf.ins(Q[i].F/2 , Q[i].S/2);
    for (int i=0;i<=ind;i++) if (Q[i].F&1) {

        int x=(Q[i].F+1)/2, y=(Q[i].S+1)/2;
        if (y <= sf.query(x))
            return 0;
    }
    return 1;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,m,q;cin>>n>>m>>q;
    for (int i=0;i<q;i++) {
        int x,y;cin>>x>>y;
        Q.pb({x,y});
    }


    int l=0,r=q;
    while(l+1<r) {
        int md=(l+r)>>1;                  //if l=m, m=(l+r+1)/2,  if r=m, m=(l+r)/2;
        if (check(md)) l=md; else r=md;
    }

    for (int i=0;i<=l;i++) cout << "YES\n";
    for (int i=l+1;i<q;i++) cout << "NO\n";

    return 0;
}