/*
            Want to query for number of 0's in a[l...r]
            This is simple modification of RSQ

            But, we want to also query for the indicie of the k'th zero. This can be done by first searching for
            2*i neighbor. If it has more than k zeros, we want to traverse there. Otherwise go to 2*i+1
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
        if (tl==tr) t[v] = a[tl]==0; //modification
        else {
            int tm = (tl+tr)/2;
            build(a, 2*v, tl, tm);
            build(a, 2*v+1, tm+1, tr);
            t[v] = t[2*v] + t[2*v+1];
        }
    }
    ll count_zero(int l,int r) { return count_zeroU(1,0,n-1,l,r);}
    ll count_zeroU(int v,int tl,int tr, int l,int r) { //value, cur l/r bounds, overall l/r bounds
        if (l > r) return 0;
        if (tl == l && tr == r) return t[v];
        int tm = (tl+tr)/2;
        return count_zeroU(2*v, tl, tm, l, min(r,tm))
                + count_zeroU(2*v+1, tm+1, tr, max(l,tm+1), r);
    }
    int kth_zero(int k) {return kth_zeroU(1,0,n-1,k);}
    int kth_zeroU(int v,int tl,int tr,int k) {
        if (k > t[v]) return -1; //there are not k zeros
        if (tl == tr) return tl;
        int tm = (tl+tr)/2;

        if (v[2*v] >= k) return kth_zeroU(2*v,tl,tm,k);
        else             return kth_zeroU(2*v+1,tm+1,tr, k-t[2*v]); //count the t[2*v] zeros in first half, search for next
    }
    //update() omited, same as RSQ
};
int main()
{
    return 0;
}