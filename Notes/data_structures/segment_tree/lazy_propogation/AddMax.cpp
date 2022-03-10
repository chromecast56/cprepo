/*
                Given array, you want to perform following operations in logn:
                    - Add a value to every element in a[l...r]
                    - Find the max value in a[l...r]
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
const int maxn = 100000;

int n;
struct SegTree {
    int t[4*maxn], lazy[4*maxn];
    void push(int v) { //push changes from vertex v
        if (!lazy[v]) return;
        t[2*v] += lazy[v];
        lazy[2*v] += lazy[v];
        t[2*v+1] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    void build(int a[],int v=1,int tl=0,int tr=n-1) {
        if (tl==tr) t[v] = a[tl];
        else {
            int tm = (tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            t[v] = max(t[2*v],t[2*v+1]);
        }
    }
    void update(int l,int r,int add) {updateU(1,0,n-1,l,r,add);}
    void updateU(int v,int tl,int tr,int l,int r,int add) {
        if (l>r) return;
        if (tl==l && tr==r)
            t[v] += add, lazy[v] += add;
        else {
            push(v);
            int tm = (tl+tr)/2;
            updateU(2*v,tl,tm,l,min(tm,r),add);
            updateU(2*v+1,tm+1,tr,max(l,tm+1),r,add);
            t[v] = max(t[2*v],t[2*v+1]);
        }
    }
    int get_max(int l,int r) {return get_maxU(1,0,n-1,l,r);}
    int get_maxU(int v,int tl,int tr,int l,int r) {
        if (l>r) return INT_MIN;
        if (l <= tl && tr <= r) return t[v];
        push(v);
        int tm = (tl+tr)/2;
        return max(get_maxU(2*v,tl,tm,l,min(tm,r)),
                   get_maxU(2*v+1,tm+1,tr,max(l,tm+1),r));
    }
};
int a[10];
int main()
{
    SegTree s;
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    s.build(a);
    s.update(1,3,5);
    s.update(3,4,-100);
    cout << s.get_max(1,3) << '\n';
    for(int i=0;i<n;i++) cout << s.get_max(i,i)<<' ';
    return 0;
}