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
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}

const int MAXN = 1000100;
/*
                Motivation: Want to speed up the n^2 brute force... One idea is iterating over horizontal, and
                logrithmically speeding up the vertical with a DS boost

                Or we can binary search on vertical! (key).
                If vertical increases, the left side increases, right side decreases
                Just compare the max (of the 2) left and rights in the bsearch! Because we minimize the lefts

                To keep track of the points in the top/bot horz divider, think of how the points progress
                They start in the top, and go to the bottom in order of y coord.
                Besides their order, we don't need their y coord when bsearching for the vertical line!

                Compress the 2d data into two 1d segment trees, top and bot. (smush it, and think of the points dropping from the top segtree to the bottom)

                One more note: A naive implementation will call the segtree sum query each bsearch, resulting in
                nlog^2n complexity for n=10^6. Too slow

                We can speed this up by a log factor because we only call prefix queries, and integrate it within the bsearch
 */
struct segtree { //typical sum segtree, but we dont need queries
    vi t;
    segtree() {
        t.resize(4*MAXN+100);
    }
    void add(int ind,int val,int tl=0,int tr=MAXN,int v = 1) {
        if (tl+1==tr) t[v] += val;
        else {
            int tm = (tl+tr)/2;
            if (ind<tm) add(ind,val,tl,tm,v*2); else add(ind,val,tm,tr,v*2+1);
            t[v] = t[v*2]+t[v*2+1];
        }
    }
};
struct DS { //data structure
    segtree top,bot; //segtree for top and bottom coordintates (according to horz divider)
    void upd(int ind) { //move a cow from top to bot
        top.add(ind,-1);
        bot.add(ind,1);
    }
    int query() { //find the minimum max number of cows by "bsearching"
        int l = 0,r = MAXN;
        //sum of each of the 4 quadrants (vertical varies)
        int nt=top.t[1],nb=bot.t[1];
        int curt=nt,curb=nb;
        int v = 1;
        while(l<r) {
            int m = (l+r)/2;
            if (max(curt,curb) > max(nt-curt,nb-curb)) {
                curt -= top.t[v*2+1]; curb -= bot.t[v*2+1];
                r = m-1; v*=2;
            }
            else if (max(curt,curb) < max(nt-curt,nb-curb)) {
                v++;
                curt += top.t[v*2]; curb += bot.t[v*2];
                l = m+1; v = v*2;
            }
            else
                l = r = m;
        }
        return max(max(curt,curb),max(nt-curt,nb-curb));
    }
};
int main()
{
    ofstream fout("balancing.out");
    ifstream fin("balancing.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;fin>>n;
    vpii a(n);
    for (int i=0;i<n;i++) fin>>a[i].F>>a[i].S;
    sort(all(a));
    DS ds;
    for (auto p: a) ds.top.add(p.S,1);

    int res = ds.query(), itr = 0;
    while(itr<n) {
        while(itr<n-1 && (itr&&a[itr].F==a[itr+1].F))
            ds.upd(a[itr++].S);

        ds.upd(a[itr++].S);
        res = min(res,ds.query());
    }

    fout << res << '\n';

    return 0;
}