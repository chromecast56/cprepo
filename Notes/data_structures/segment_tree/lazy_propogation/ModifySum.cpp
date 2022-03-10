/*
                Given array, you want to perform following operations in logn:
                    - Modify every element in a[l...r]
                    - Find the sum of a[l...r]
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
    int t[4*maxn], lazy[4*maxn]; //Remember fill lazy with UNUSED
    void push(int v,int L) { //push changes from vertex v
        if (lazy[v] == UNUSED) return;
        t[2*v] = (L-L/2)*lazy[v];
        lazy[2*v] = lazy[v];
        t[2*v+1] = (L/2)*lazy[v];
        lazy[2*v+1] = lazy[v];
        lazy[v] = UNUSED;
    }
    void build(int a[],int v=1,int tl=0,int tr=n-1) {
        if (tl==tr) t[v] = a[tl];
        else {
            int tm = (tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            t[v] = t[2*v] + t[2*v+1];
        }
    }
    void update(int l,int r,int nval) {updateU(1,0,n-1,l,r,nval);}
    void updateU(int v,int tl,int tr,int l,int r,int nval) {
        if (l>r) return;
        if (tl==l && tr==r)
            t[v] = (tr-tl+1)*nval, lazy[v] = nval;
        else {
            push(v,tr-tl+1);
            int tm = (tl+tr)/2;
            updateU(2*v,tl,tm,l,min(tm,r),nval);
            updateU(2*v+1,tm+1,tr,max(l,tm+1),r,nval);
            t[v] = t[2*v] + t[2*v+1];
        }
    }
    int sum(int l,int r) {return sumU(1,0,n-1,l,r);}
    int sumU(int v,int tl,int tr,int l,int r) {
        if (l>r) return 0;
        if (l <= tl && tr <= r) return t[v];
        push(v,tr-tl+1);
        int tm = (tl+tr)/2;
        return sumU(2*v,tl,tm,l,min(tm,r)) +
                   sumU(2*v+1,tm+1,tr,max(l,tm+1),r);
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
    cout << s.sum(1,3) << '\n';
    for(int i=0;i<n;i++)
        cout << s.sum(i,i)<<' ';
    s.update(0,1,0);
    cout <<'\n'<< s.sum(0,4) << '\n';
    for (int i=0;i<n;i++) cout << s.sum(i,i) << ' ';
    return 0;
}