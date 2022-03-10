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
int n, t[4*maxn];
struct segtree {
    ll t[5000000];
    ll query(int l,int r, int tl=0,int tr=1000100, int v=1) { //value, cur l/r bounds, overall l/r bounds
        if (l >= r) return 0;
        if (tl == l && tr == r) return t[v];
        int tm = (tl+tr)/2;
        return max(query(l,min(tm,r),tl,tm,v*2)
                , query(max(tm,l),r,tm,tr,v*2+1));
    }
    void upd(int ind,int val,int tl=0,int tr=1000100,int v=1) {
        if (tl+1==tr) t[v] = val;
        else {
            int tm = (tl+tr)/2;
            if (ind<tm) upd(ind,val,tl,tm,v*2);
            else upd(ind,val,tm,tr,v*2+1);

            t[v] = max(t[v*2],t[v*2+1]);
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
        cout << s.get_max(i,i) << ' ';
    cout<<endl;
    for (int i=0;i<n-1;i++)
        cout << s.get_max(i,i+1) << ' ';
    return 0;
}