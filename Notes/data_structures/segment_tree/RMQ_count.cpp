/*
            RMQ with a twist: Not only do we want to find the max value in a[l...r] (dynamically)
            , we also want to find the number of times it appears

            In this case, for each node we will store two values, the max val and # times it occurs.
            To combine two nodes we use our own method, instead of p = max(n1,n2)
 */
/*
            Want to create a segment tree that:
                - Can compute max of a[l...r]
                - Can update elements of a
            In logn time
            This can be expanded to min queries easily
 */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int maxn = 100000;
int n;
pi t[4*maxn];
struct SegTree
{
    pi combine(pi a,pi b) {
        if (a.first > b.first) return a;     // >
        if (a.first < b.first) return b;     // <
        return {a.first, a.second+b.second}; // =
    }
    void build(int a[], int v=1,int tl=0,int tr=n-1) { //arr, value, cur l/r bounds, overall l/r bounds
        if (tl==tr) t[v] = {a[tl],1};
        else {
            int tm = (tl+tr)/2;
            build(a, 2*v, tl, tm);
            build(a, 2*v+1, tm+1, tr);
            t[v] = combine(t[2*v], t[2*v+1]);
        }
    }
    pi get_max(int l,int r) { return get_maxU(1,0,n-1,l,r);}
    pi get_maxU(int v,int tl,int tr, int l,int r) { //value, cur l/r bounds, overall l/r bounds
        if (l > r) return {INT_MIN,0};
        if (tl == l && tr == r) return t[v];
        int tm = (tl+tr)/2;
        return combine(get_maxU(2*v, tl, tm, l, min(r,tm))
                , get_maxU(2*v+1, tm+1, tr, max(l,tm+1), r));
    }
    void update(int pos,int nval) {return updateU(1,pos,0,n-1,nval);}
    void updateU(int v,int pos,int tl,int tr,int nval) {
        if (tl==tr) t[v] = {nval,1};
        else {
            int tm = (tl+tr)/2;
            if (pos<=tm) updateU(2*v, pos, tl, tm, nval);
            else updateU(2*v+1, pos, tm+1, tr, nval);
        }
    }
};
int a[5];
void print(pi res) {cout<<'['<<res.first<<", "<<res.second<<"] ";}
int main()
{
    SegTree s;
    cin >> n;
    for (int i=0;i<n;i++) cin>>a[i];
    s.build(a);
    s.update(2,10);
    for (int i=0;i<n;i++)
        print(s.get_max(i,i));
    cout<<endl;
    for (int i=0;i<n-1;i++)
        print(s.get_max(i,i+1));
    return 0;
}