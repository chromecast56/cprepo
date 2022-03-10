/*
            Want to create a segment tree that:
                - Can compute sum of a[l...r]
                - Can update elements of a
            In logn time
 */
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int maxn = 100000;
int n, t[4*maxn];
struct SegTree
{
    void build(int a[], int v=1,int tl=0,int tr=n-1) { //arr, value, cur l/r bounds, overall l/r bounds
        if (tl==tr) t[v] = a[tl];
        else {
            int tm = (tl+tr)/2;
            build(a, 2*v, tl, tm);
            build(a, 2*v+1, tm+1, tr);
            t[v] = t[2*v] + t[2*v+1];
        }
    }
    ll sum(int l,int r) { return sumU(1,0,n-1,l,r);}
    ll sumU(int v,int tl,int tr, int l,int r) { //value, cur l/r bounds, overall l/r bounds
        if (l > r) return 0;
        if (tl == l && tr == r) return t[v];
        int tm = (tl+tr)/2;
        return sumU(2*v, tl, tm, l, min(r,tm))
             + sumU(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
    void update(int pos,int nval) {return updateU(1,pos,0,n-1,nval);}
    void updateU(int v,int pos,int tl,int tr,int nval) {
        if (tl==tr) t[v] = nval;
        else {
            int tm = (tl+tr)/2;
            if (pos<=tm) updateU(2*v, pos, tl, tm, nval);
            else updateU(2*v+1, pos, tm+1, tr, nval);
        }
    }
};
int a[5];
int main()
{
    SegTree s;
    cin >> n;
    for (int i=0;i<n;i++) cin>>a[i];
    s.build(a);
    s.update(2,10);
    for (int i=0;i<n;i++)
        cout << s.sum(i,i) << ' ';
    cout<<endl;
    for (int i=0;i<n-1;i++)
        cout << s.sum(i,i+1) << ' ';
    return 0;
}