/*
                    Sometimes you want to (read: the problem wants to) query on a segment tree, except on a past
                    iteration of it. Ex. queries are of form (k,l,r), where you want to find sum of a[l..r],
                    on the kth iteration array.

                    To do this faster than simply copying the segtree at each update/iteration, we can note that
                    in each update, only logn vertexes are updated. This means that if we maintain the vertexes as
                    pointers, we can simply switch out the logn vertexes into new ones.
                    During implementation, since the root vertex is always changed, we simply maintain an array
                    of every iteration of the root vertex to store the info.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;

int n;
struct Vertex
{
    Vertex *l, *r; int sum; //maintain left/right children
    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {} //for leaf nodes
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum+=l->sum;
        if (r) sum+=r->sum;
    }
};
Vertex* build(int a[],int tl=0,int tr=n-1) {
    if (tl==tr) return new Vertex(a[tl]);
    else {
        int tm = (tl+tr)/2;
        return new Vertex(build(a,tl,tm),build(a,tm+1,tr));
    }
}
int sum(Vertex *v,int l,int r,int tl=0,int tr=n-1) {
    if (l > r) return 0;
    if (l==tl && r==tr) return v->sum;
    int tm = (tl+tr)/2;
    return sum(v->l,l,min(tm,r),tl,tm) + sum(v->r,max(l,tm+1),r,tm+1,tr);
}
Vertex* update(Vertex *v,int pos,int nval,int tl=0,int tr=n-1) {
    if (tl==tr) return new Vertex(nval); //new Vertex(nval + v->sum) for addition
    int tm = (tl+tr)/2;
    if (pos<=tm)
        return new Vertex(update(v->l,pos,nval,tl,tm),v->r);
    else
        return new Vertex(v->l,update(v->r,pos,nval,tm+1,tr));
}
int a[10];
Vertex* verts[10];
void print(int ind) {for(int i=0;i<n;i++)cout<<sum(verts[ind],i,i)<<' ';cout<<'\n';}
int main()
{
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    verts[0] = build(a);
    verts[1] = update(verts[0],0,5);
    cout << sum(verts[1],0,2) <<'\n';
    print(1);
    
    return 0;
}
