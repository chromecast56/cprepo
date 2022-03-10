/*
                Given array, you want to perform following operations in logn:
                    - Modify every value in a[l...r]
                    - Find the max value in a[l...r]
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
const int maxn = 100000;
const int UNUSED = INT_MIN; //define unused var to default to (can't default to 0 anymore)

int n;
struct SegTree {
    int t[4*maxn], lazy[4*maxn]; //Remember to fill lazy with UNUSED
    void push(int v) { //push changes from vertex v
        if (lazy[v] == UNUSED) return;
        t[2*v] = lazy[v];
        lazy[2*v] = lazy[v];
        t[2*v+1] = lazy[v];
        lazy[2*v+1] = lazy[v];
        lazy[v] = UNUSED;
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
    void update(int l,int r,int nval) {updateU(1,0,n-1,l,r,nval);}
    void updateU(int v,int tl,int tr,int l,int r,int nval) {
        if (l>r) return;
        if (tl==l && tr==r)
            t[v] = nval, lazy[v] = nval;
        else {
            push(v);
            int tm = (tl+tr)/2;
            updateU(2*v,tl,tm,l,min(tm,r),nval);
            updateU(2*v+1,tm+1,tr,max(l,tm+1),r,nval);
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
    fill(lazy,lazy+20,UNUSED);
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    s.build(a);
    s.update(1,3,5);
    s.update(3,4,-100);
    cout << s.get_max(1,3) << '\n';
    for(int i=0;i<n;i++) cout << s.get_max(i,i)<<' ';
    s.update(0,1,0);
    cout <<'\n'<< s.get_max(0,4) << '\n';
    for (int i=0;i<n;i++) cout << s.get_max(i,i) << ' ';
    return 0;
}