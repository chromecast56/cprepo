/*
            The problem with the merge sort tree implementation is that it doesn't allow for modifications, since
            modifying the subarrays makes them unsorted. It takes O(n) to move the changed value to the correct spot,
            making the implementation useless.

            Instead of using arrays, we can use multisets (or maps). They are red-black trees, and also support
            std::merge, and insertion/deletion/modification in O(1)
            (note: unordered_multiset may be faster, but it doesn't support std::merge)

            Time complexity is unchanged (technically building is now O(nlog^2n), but in practice it's still O(n))
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int maxn = 1e5;
int n;
multiset<int> t[4*maxn];
int a[maxn];
struct SegTree
{
    void build(int a[],int v=1,int tl=0,int tr=n-1) {
        if (tl==tr) t[v].insert(a[tl]);
        else {
            int tm = (tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            merge(t[2*v].begin(),t[2*v].end(),t[2*v+1].begin(),t[2*v+1].end(), inserter(t[v],t[v].begin())); //built in merge sort
        }
    }
    int query(int l,int r,int x) {return queryU(1,0,n-1,l,r,x);}
    int queryU(int v,int tl,int tr,int l,int r,int x) {
        if (l > r) return INT_MAX;
        if (tl == l && tr == r) {
            auto itr = t[v].lower_bound(x); //remember to use multiset lb! std::lb is only log(n) for arrays
            if (itr==t[v].end()) return INT_MAX;
            return *itr; //dereferencing returns value, not indicie
        }
        int tm = (tl+tr)/2;
        return min(queryU(2*v, tl, tm, l, min(tm,r), x)
                , queryU(2*v+1, tm+1, tr, max(l,tm), r, x));
    }
    void update(int pos,int nval) {return updateU(1,pos,0,n-1,nval);}
    void updateU(int v,int pos,int tl,int tr,int nval) {
        t[v].erase(t[v].find(a[pos])); //remember to modify each vertex, not just tl==tr!
        t[v].insert(nval);

        if (tl == tr) a[pos] = nval;
        else {
            int tm = (tl+tr)/2;
            if (tm <= pos) updateU(2*v,pos,tl,tm,nval);
            else           updateU(2*v+1,pos,tm+1,tr,nval);
        }
    }
};
int main()
{

    return 0;
}