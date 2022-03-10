/*
                            Problem, have array, want to answer queries in form (i,j,k), saying:
                            What is k'th smallest element in subarray [i...j]?

                            Easier subtask: What if you do it with only prefixes (i.e. i=1), and numbers are
                            in 1 <= a_i <= n?
                            You can use persistent segtree, and insert the values from least index to most index,
                            where (ind = index of a_i, and val = 1), like a frequency table.
                            Then, we can use the persistency of the segtree to answer queries using k'th zero
                            RSQ strategies. Ex for query (i,k), where want to find k'th number on prefix [1...i],
                            we go to the i'th segtree and do k'th val RSQ.

                            For the harder problem, note that the values can be compressed using unordered_set.
                            Then for queries


                            O(logn) query with little overhead
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int MAXN = 100100;

int n,q;
struct node
{
    node *l, *r;
    int v;
    node(int v) : l(nullptr), r(nullptr), v(v) {}
    node(node *ll, node *rr) : l(ll), r(rr), v(l->v+r->v) {}
};
node* build(int *A, int l=0,int r=MAXN) //range [l,r)
{
    if (l+1==r) return new node(A[l]);
    int m = (l+r)>>1;
    return new node(build(A,l,m),build(A,m,r));
}
node* update(int ind,int val,node *vert,int l=0,int r=MAXN)
{
    if (l+1==r) return new node(val);
    int m = (l+r)>>1;
    if (m > ind)
        return new node(update(ind,val,vert->l,l,m), vert->r);
    return new node(vert->l, update(ind,val,vert->r,m,r));
}
int num(node *v_i,node *v_j) { //calculate difference of nodes in i and j
    return v_j->v - v_i->v;
}
int kth(node *v_i, node *v_j, int k,int l=0,int r=MAXN)
{
    if (k > num(v_i,v_j)) return -1;
    if (l+1==r) return l;
    int m = (l+r)>>1;
    if (k <= num(v_i->l,v_j->l))
        return kth(v_i->l,v_j->l,k,l,m);
    return kth(v_i->r, v_j->r, k - num(v_i->l,v_j->l) ,m,r);
}
int A[MAXN], B[MAXN]; //B is helper to sort
unordered_map<int,int> a_to_i, sorti_to_a, a_to_sorti;
vector<node*> nodes;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin >> n >> q;

    node* blank = build(A);
    for (int i=1;i<=n;i++) {
        cin >> A[i];
        B[i] = A[i];
        a_to_i[A[i]] = i;
    }
    sort(B+1,B+n+1);
    for (int i=1;i<=n;i++) a_to_sorti[B[i]] = i, sorti_to_a[i] = B[i];
    nodes.push_back(blank);
    for (int i=1;i<=n;i++)
        nodes.push_back(update(a_to_sorti[A[i]],1,nodes[i-1]));

    while(q--)
    {
        int i,j,k;
        cin >> i >> j >> k;
        int kth_i = kth(nodes[i-1],nodes[j],k);
        cout << sorti_to_a[kth_i] << '\n'; //use psum to find ans
    }

    return 0;
}