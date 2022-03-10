/*
ID: jamesli5
PROG: prefix
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int maxn = 100100;

int n,q;
pii p[maxn];
int a[maxn];
struct SegTree
{
    int t[4*maxn];
    bool b; //b=0 if sum, b=1 if max
    void build(int *A, int v=1,int l=0,int r=n+1) {
        if (l+1==r) {
            t[v] = A[l];
            return;
        }
        int m = (l+r)>>1;
        build(A,v*2,l,m);
        build(A,v*2+1,m,r);
        t[v] = b? std::max(t[2*v],t[2*v+1]) : t[2*v]+t[2*v+1];
    }
    void update(int ind,int val,int v=1,int l=0,int r=n+1) {
        if (l+1==r) {
            t[v] = val;
            return;
        }
        int m = (l+r)>>1;
        if (m > ind)
            update(ind,val,v*2,l,m);
        else
            update(ind,val,v*2+1,m,r);
        t[v] = b? std::max(t[2*v],t[2*v+1]) : t[2*v]+t[2*v+1];
    }
    int query(int l,int r,int v=1,int tl=0,int tr=n+1) {
        if (l >= tr || r <= tl) return 0;
        if (l <= tl && r >= tr)
            return t[v];
        int tm = (tl+tr)>>1;
        if (b)
            return max(query(l,r,v*2,tl,tm),query(l,r,v*2+1,tm,tr));
        else
            return query(l,r,v*2,tl,tm) + query(l,r,v*2+1,tm,tr);
    }
};
SegTree s,m;
//query methods
int sum(int l,int r) { //find sum from l to r
    return s.query(l,r);
}
int delta(int l,int r) { //find maximum delta. Define delta_i the time saved by skipping checkpoint i
    return m.query(l+1,r); //remember can't skip first pnt or last pnt!
}
int dist(pii &p1,pii &p2) { //distance between two points
    return abs(p1.F-p2.F) + abs(p1.S-p2.S);
}
void update(int i,int x,int y) { //add segree m also
    p[i].F = x;
    p[i].S = y;
    if (i != 1) s.update(i-1,dist(p[i-1],p[i]));
    if (i != n) s.update(i,dist(p[i],p[i+1]));

    for (int j=i-1; j<=i+1; j++)
        if (j-1 >= 1 && j+1 <= n) {
            int nval = a[j] = dist(p[j-1],p[j])+dist(p[j],p[j+1]) - dist(p[j-1],p[j+1]);
            m.update(j,nval);
        }
}
int main()
{
    ofstream fout("marathon.out");
    ifstream fin("marathon.in");
    ios_base::sync_with_stdio(false);
    fin.tie();
    fin>>n>>q;
    for (int i=1;i<=n;i++)
        fin >> p[i].F >> p[i].S;

    s.b=0, m.b=1;
    for (int i=1;i<=n;i++)
        a[i] = dist(p[i],p[i+1]);
    s.build(a);
    memset(a,0,sizeof(a));
    for (int i=2;i<=n-1;i++)
        a[i] = dist(p[i-1],p[i])+dist(p[i],p[i+1]) - dist(p[i-1],p[i+1]);
    m.build(a);

    while(q--) {
        char type; fin>>type;
        if (type=='Q') {
            int l,r;
            fin>>l>>r;
            fout<<sum(l,r)-delta(l,r) << endl;
        }
        else {
            int i,x,y;
            fin>>i>>x>>y;
            update(i,x,y);
        }
    }

    return 0;
}