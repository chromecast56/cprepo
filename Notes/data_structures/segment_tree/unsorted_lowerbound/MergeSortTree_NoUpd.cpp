/*
            You're given an array, and want to answer queries in form (l,r,x), which asks for the smallest
            in subarray a[l...r] such that it is >= x. Assume no modifications (will do updates in later code)

            The key idea is that each vertex can store its own entire subarray, resulting in O(nlogn) memory.
            In build function, we can use a "merge sort" like combine function (included in stl) so each vertex stores
            its subarrays in sorted order.

            Then, for query time, we can just std::lower_bound on each covered vertex and take the min.
            For simplicity's sake, assume that no answer is found when INT_MAX is outputed

            There are logn queryU and each one takes logn for lower_bound, so overal query complexity is log^2n
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int maxn = 1e5;
int n;
vi t[4*maxn];
struct SegTree
{
    void build(int a[],int v=1,int tl=0,int tr=n-1) {
        if (tl==tr) t[v] = vi(1,a[tl]);
        else {
            int tm = (tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            merge(t[2*v].begin(),t[2*v].end(),t[2*v+1].begin(),t[2*v+1].end(), back_inserter(t[v])); //built in merge sort
        }
    }
    int query(int l,int r,int x) {return queryU(1,0,n-1,l,r,x);}
    int queryU(int v,int tl,int tr,int l,int r,int x) {
        if (l > r) return INT_MAX;
        if (tl == l && tr == r) {
            auto itr = lower_bound(t[v].begin(),t[v].end(), x);
            if (itr==t[v].end()) return INT_MAX;
            return *itr; //dereferencing returns value, not indicie
        }
        int tm = (tl+tr)/2;
        return min(queryU(2*v, tl, tm, l, min(tm,r), x)
                  , queryU(2*v+1, tm+1, tr, max(l,tm), r, x));
    }
};
int main()
{

    return 0;
}