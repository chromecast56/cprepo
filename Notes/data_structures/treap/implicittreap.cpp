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
            Currently, the ds supports the following operations in logn time:
            - Insertion of (key,val) pairs
            - Deletion of (key,val) pairs
            - Subarray sum query
            - Reverse on subarray
            - Implicit indexing

            Things to do:
                - lazy propogation
                - Clean up code
 */
struct node { //verticies of the treap (randomized bst)
    int cnt = 1,prio;
    ll val, cval;
    bool rev = 0; //lazy propagation
    node *l,*r;
    node(){}
    node(int val) : val(val), cval(val), prio(rng()%INT_MAX), l(NULL), r(NULL) {}
    node(int val,int prio) : val(val), cval(val), prio(prio), l(NULL), r(NULL) {}
};
//pointer node
typedef node* pnode;
struct treap {
    pnode root = NULL;
private:
    int cnt(pnode it) {return it ? it->cnt : 0;}
    ll cval(pnode it) {return it ? it->cval : 0;}
    void push(pnode t) { //push before, lazy propagation
        if (!t) return;
        if (t->rev) {
            t->rev = 0;
            swap(t->l,t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
        }
    }
    void upd(pnode t) { //upd after
        if(t)
            t->cnt = 1+cnt(t->l)+cnt(t->r),
            t->cval = t->val + cval(t->l)+cval(t->r);
    }
    void lr(pnode &p) {pnode R = p->r; pnode X = p->r->l;R->l = p; p->r= X; p = R;}
    void rr(pnode &p) {pnode L = p->l; pnode Y = p->l->r;L->r = p; p->l= Y; p = L;}
    void ins(pnode &t,int add,int key,int val,int prio = 0) { //insert in subtree of t, prio = 1 if splitting
        if (t==NULL) {
            t = prio? new node(val,INT_MAX) : new node(val); //split ins, regular ins
            return;
        }
        push(t);
        if (t->l) upd(t->l); if (t->r) upd(t->r); upd(t);
        int cur_key = add + cnt(t->l);
        if (key<=cur_key) {
            ins(t->l,add,key,val,prio);
            if (t->l != NULL && t->l->prio > t->prio)
                rr(t);
        }
        else {
            ins(t->r,1+cur_key,key,val,prio);
            if (t->r != NULL && t->r->prio > t->prio)
                lr(t);
        }
        if (t->l) upd(t->l); if (t->r) upd(t->r); upd(t);
    }
    void split(pnode &t,int key,pnode &l,pnode &r) { //splits subtree of t and destroys t in the process (in l < x, in r >= x)
        ins(t,0,key,0,1);
        tie(l,r) = {t->l,t->r};
        t = NULL;
    }
    void merge(pnode &t,pnode l,pnode r) { //t becomes the merge of l and r
        push(l); push(r);
        if (!l||!r)
            t = l? l:r;
        else if (l->prio > r->prio) merge(l->r,l->r,r), t = l;
        else                        merge(r->l,l,r->l), t = r;
        if (t!=NULL) upd(t);
    }
    ll search(pnode &t,int add,int key,bool b) { //0 = delete, 1 = get
        if (t==NULL) return -1;
        push(t);
        int cur_key = add + cnt(t->l); ll res = 0;
        if (cur_key==key) {
            if (!b) {
                pnode th = t;
                merge (t, t->l, t->r);
                delete th;return -1;
            }
            else return t->val;
        }
        else
        if (key<=cur_key) res = search(t->l,add,key,b);
        else              res = search(t->r,1+cur_key,key,b);

        upd(t);
        return res;
    }
public:
    int size() {return root->cnt;}
    void ins(int key,int val) {ins(root,0,key,val);}
    void del(int key) {search(root,0,key,0);}
    ll get(int key) {search(root,0,key,1);}
    ll operator[](int key) {
        if (key < 0 && root->cnt <= key) {cout << "OOB\n"; return -1;}
        return search(root,0,key,1);
    }
    ll query(int l,int r) { //[l,r)
        pnode x,a,b,c;
        split(root,r,x,c); split(x,l,a,b);
        ll res = b->cval;
        merge(x,a,b); merge(root,x,c);
        return res;
    }
    void reverse(int l,int r) {
        pnode x,a,b,c;
        split(root,r,x,c); split(x,l,a,b);
        b->rev ^= 1;
        merge(x,a,b); merge(root,x,c);
    }
    void shift(int l,int r) {
        ll x = search(root,0,r-1,1);
        del(r-1);
        ins(l,x);
    }
};
int main()
{
    treap t;
    int n,q,m;cin>>n>>q>>m;
    for (int i=0;i<n;i++) {
        int x;cin>>x;
        t.ins(i,x);
    }
    while(q--) {
        int typ,l,r;cin>>typ>>l>>r;
        l--,r--;
        if (typ==1) t.shift(l,r+1);
        else        t.reverse(l,r+1);
    }

    while(m--) {
        int x;cin>>x;
        cout << t[x-1] << ' ';
    }
    cout << endl;

    return 0;
}