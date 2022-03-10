#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
typedef vector<pii> vpii; typedef vector<pll> vpll;
#define F first
#define S second
#define sz(x) (int) (x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pb push_back
const int MOD = 1e9+7; //998244353
const int MX = 2e5+100;
const ll INF = 1e18;

#include <ext/pb_ds/tree_policy.hpp> //set but with more operations: Tree<T>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;                                 //order_of_key(x) - find # elements less than x, index Set greater<> for comparator if needed
template <class T> using Tree = tree<T, null_type, less<T>,               //find_by_order(x) - return iterator to x lowest value (0 based), value
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
void sort(vector<t> &a) {return sort(a.begin(),a.end());}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/*
            Currently, the treap supports the following operations in logn time:
            - Insertion of (key,val) pairs
            - Deletion of (key,val) pairs
            - Subarray sum query, arbitrary indicies!

            Things to do:
                - lazy propogation
                - Implicit indexing
                - Reverse on subarray
                - Clean up code
 */
struct node { //verticies of the treap (randomized bst)
    int key,prio;
    ll val, cval;
    node *l,*r;
    node(){}
    node(int key,int val) : key(key), val(val), cval(val), prio(rng()%INT_MAX), l(NULL), r(NULL) {}
    node(int key,int val,int prio) : key(key), val(val), cval(val), prio(prio), l(NULL), r(NULL) {}
    void upd() {
        cval = val + (l == NULL? 0:l->cval) + (r == NULL? 0:r->cval);
    }
};
//pointer node
typedef node* pnode;
struct treap {
    pnode root = NULL;
private:
    void lr(pnode &p) {
        pnode R = p->r; pnode X = p->r->l;
        R->l = p; p->r= X; p = R;
        p->l->upd();
    }
    void rr(pnode &p) {
        pnode L = p->l; pnode Y = p->l->r;
        L->r = p; p->l= Y; p = L;
        p->r->upd();
    }
    void ins(pnode &t,int key,int val,int prio = 0) { //insert in subtree of t, prio = 1 if splitting
        if (t==NULL) {
            t = prio? new node(key,val,INT_MAX) : new node(key,val); //split ins, regular ins
            return;
        }
        if (key<=t->key) {
            ins(t->l,key,val,prio);
            if (t->l != NULL && t->l->prio > t->prio)
                rr(t);
        }
        else {
            ins(t->r,key,val,prio);
            if (t->r != NULL && t->r->prio > t->prio)
                lr(t);
        }
    }
    void split(pnode &t,int key,pnode &l,pnode &r) { //splits subtree of t and destroys t in the process (in l < x, in r >= x)
        ins(t,key,0,1);
        tie(l,r) = {t->l,t->r};
        t = NULL;
    }
    void merge(pnode &t,pnode l,pnode r) { //t becomes the merge of l and r
        if (!l||!r)
            t = l? l:r;
        else if (l->prio > r->prio)
            merge(l->r,l->r,r), t = l;
        else
            merge(r->l,l,r->l), t = r;
        t->upd();
    }
    void del(pnode &t,int key) {
        if (t==NULL) return;
        if (t->key==key) {
            pnode th = t;
            merge (t, t->l, t->r);
            delete th;
        }
        else
            del(key <= t->key? t->l:t->r, key);
    }
public:
    void ins(int key,int val) {ins(root,key,val);}
    void del(int key) {del(root,key);}
    ll query(int l,int r) { //[l,r)
        pnode x,a,b,c;
        split(root,l,a,x);
        split(x,r,b,c);
        ll res = b->cval;
        merge(x,b,c); merge(root,a,x);
        return res;
    }
};
int main()
{
    treap t;

    vl a = {10,30,20,40,5,70};
    for (int i=0;i<sz(a);i++)
        t.ins(i,a[i]);

    cout << t.query(0,3) << '\n';
    cout << t.query(1,5) << '\n';
    return 0;
}