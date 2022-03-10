/*
                    For a subarray a[l...r], define:
                                - K_i, number of occurences of i
                                - Cost, the sum of K_i*K_i*i for all i
            Query for Q subarray costs

            Here you can use Mo's algorithm

            Extra practice: How could you modify this to allow for updates?
            https://paste.ubuntu.com/24872237/ for reference
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int MAXN = 200100;

int n,t;
int a[MAXN];
int cnt[1000010];
int mo_l = 1, mo_r = 0;
ll res[MAXN], global_ans=0;

int SQRTN;
void add(int v) {
    global_ans += v*(2*cnt[v]+1);
    cnt[v]++;
}
void remove(int v) {
    global_ans -= v*(2*cnt[v]-1);
    cnt[v]--;
}
struct query
{
    int l,r,i;
    bool operator<(const query &q) const { //update < method to one shown in MOsUpdate
        if (l/SQRTN != q.l/SQRTN)
            return l < q.l;
        return r < q.r;
    }
};
/*
 * Update queries {{ind,val},prev_val}
void update(int t,int l,int r,bool b) { //0 = rollback, 1 = update
    if (l <= upd_list[t].ind) <= r {       //while doing this, queries need extra para 't' for # updates done before,
         if (!b)
            remove(upd_list[i].val),
            add(upd_list[i].prev_val) //also need vector of update queries to match by indicie
          else
            remove(upd_list[i].prev_val),
            add(upd_list[i].val)
    }
 }
 */
query q[MAXN];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    scanf("%d%d",&n,&t);
    SQRTN = pow(n,0.5);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=0;i<t;i++) scanf("%d%d",&q[i].l,&q[i].r), q[i].i=i; //add some sort of update counter and vector
    sort(q,q+t);

    for (int i=0;i<t;i++)
    {
        /*
        while(mo_t<q[i].t)
            mo_t++, update(q[i].t, q[i].l, q[i].r, 0)
        while(mo_t>q[i].t)
            update(q[i].t, q[i].l, q[i].r, 1), mo_t--;
         */
        while(mo_r<q[i].r)
            mo_r++, add(a[mo_r]);
        while(mo_r>q[i].r)
            remove(a[mo_r]), mo_r--;
        while(mo_l<q[i].l)
            remove(a[mo_l]), mo_l++;
        while(mo_l>q[i].l)
            mo_l--, add(a[mo_l]);

        res[q[i].i] = global_ans;
    }
    for (int i=0;i<t;i++)
        cout << res[i] << '\n';

    return 0;
}
