/*
                Simple problem: Given an array, what is the maximal sum of one of its subsegments?
                (0 <= i <= j < N, want to max sum a[i...j])
                This can be done with a single sweep, resetting sum to 0 if it ever goes negative

                But how do you solve the dynamic version? i.e., Given an array, you're given queries of subsegments
                in form (l,r). The goal is to find the max subsegment sum for each of them in logn time.
                (Of course, you also want single element modifications)

                This is a more complicated segtree problem. For the t[] array, we want to store the following for each node:
                    - Total sum
                    - Max prefix sum
                    - Max suffix sum
                    - Its answer (computed from 2*i and 2*i+1)

                 Combine function for res (from a,b) will be:
                    - Total sum = a.sum+b.sum
                    - Prefix sum = max(a.pref, a.sum+b.pref)
                    - Suffix sum = max(b.suf, b.sum+a.suf)
                    - answer = max(a.ans,b.ans,a.suf+b.pref)

                    For single elements the data is either a[i] or 0 depending on sign
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

const int maxn = 1e5;
struct data {
    int sum, pref,suf,ans;
};
int n;
data t[4*maxn];
struct SegTree
{
    data make_data(int val) {
        if (val) return {val,val,val,val};
        return {val,0,0,0};  //still include total sum
    }
    data combine(data a,data b) {
        data res;
        res.sum = a.sum+b.sum;
        res.pref = max(a.pref,a.sum+b.pref);
        res.suf = max(b.suf,b.sum+a.suf);
        res.ans = max(max(a.sum,b.sum), a.suf+b.pref);
        return res;
    }
    void build(int a[],int v=1, int tl=0, int tr=n-1) {
        if (tl==tr) t[v] = make_data(a[tl]);
        else {
            int tm = (tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            t[v] = combine(t[2*v], t[2*v+1]);
        }
    }
    ll max_sum(int l,int r) {return max_sumU(1,0,n-1,l,r);}
    ll max_sumU(int v,int tl,int tr,int l,int r) {
        if (tl > tr) return 0;
        if (tl == tr) return t[v].ans;
        int tm = (tl+tr)/2;
        return max(max_sumU(2*v, tl, tm, l, min(tm,r))
                 , max_sumU(2*v+1, tm+1, tr, max(l,tm+1), tr));
    }
    void update(int pos, int nval) {return updateU(1,pos,0,n-1,nval);}
    void updateU(int v,int pos,int tl,int tr,int nval) {
        if (tl==tr) t[v] = make_data(nval);
        else {
            int tm = (tl+tr)/2;
            if (pos <= tm) updateU(2*v,pos,tl,tm,nval);
            else           updateU(2*v+1,pos,tm+1,tr,nval);
            t[v] = combine(t[2*v], t[2*v+1]);
        }
    }
};
int main()
{
    return 0;
}