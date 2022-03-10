/*
                            Always want to clump letters together. Ex. in strings aab, abc, we have operations a->b, a->c, b->c
                            Better to do a->b, b->c

                            Now we make a graph, with edges (u,v) present if a[i]=u and b[i]=v (make u into v)

                            Easy subtask (no cycles):
                                The graph is a DAF, with each component a DAG. This means that for each component,
                                we can simply snowball the values in the topological sort.
                                ans = sum of |comp|-1 for every component

                            Hard subtask(cycles):
                                For every component:
                                    Some verticies we only visit once, and some we visit at most twice (never more).
                                    Visiting a verticie more than once will waste operations

                                    We have some verticies we only visit once. This is kind of like the easy subtask,
                                    and any subset of these verticies will form a DAG/DAF.

                                    So, if we have |DAG| verticies we only visit once, we have n-|DAG| verticies we
                                    visit twice.

                                    For example, we can visit the "2" verticies first, then the "1" to "shuttle" the "2"s,
                                    then the "2" again. Or we can visit the "2", then visit them again to finalize them,
                                    then finally visit the "1" DAG by itself.

                                    We spend |DAG|-1 operations traversing the DAG and 2n-2|DAG| operations on the "2"s.

                                    This results in an answer of 2n-|DAG|-1 for each component, where n is |comp|

                                    Obviously we want to maximize |DAG|, and visit as much verticies as possible only once
                                    But we can't simply tell if we will visit a verticie only once
                                    How to do this? We can do bitmask dp


                                    dp[0] = 1;
                                    for msk 0...2^n-1
                                        for j 0...comp
                                            if dp[msk-2^j]==1  (set without j works)
                                            and reach[j] & msk-2^j == 0 (and j does not connect into any element in the set)
                                            dp[msk] = 1;

                                    In short. for every mask we iterate over the head of its topological sort. The head
                                    obviously cant connect into any of the mask's elements (otherwise itd create a loop)


                            Of course very implementation heavy (3100 rating!)

                            Some issues/things to consider next time:
                                - Remember that when working with directed graphs, verticies shouldn't connect to themselves
                                (otherwise it messes with DAG/SCC stuff)

                                - Always use dsu to find weakly connected components, simple dfs won't work and if you try to
                                make it work, implementation gets rough

                                - The reach[] array caused lots of bugs because in each component, letters were represented by 0...sz-1
                                in the bitmask, but were represented by their actual value/letter in reach[].
                                Solution is either to construct the reach array from scratch for each component, or if
                                that way is too messy, to have a global_reach[], and in each component construct a
                                reach[] that is a transform of global_reach[] (which is what I did).

 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii; typedef pair<ll,ll> pll;
typedef vector<int> vi; typedef vector<ll> vl;
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
#include <ext/pb_ds/assoc_container.hpp>    //order_of_key(x) - find # elements less than x, index
using namespace __gnu_pbds;                 //find_by_order(x) - return iterator to x lowest value (0 based), value
template <class T> using Tree = tree<T, null_type, less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;
template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}
struct dsu {

    vi p,sz;
    dsu(int n) {p.resize(n),sz.resize(n);for (int i=0;i<n;i++)p[i]=i,sz[i]=1;}
    int find(int u) {
        if (p[u] == u) return u;
        return p[u] = find(p[u]);
    }
    void merge(int u,int v) {
        u = find(u), v = find(v);
        if (u!=v) {
            if (sz[u]<sz[v]) swap(u,v);
            p[v]=u;
            sz[u]+=sz[v];
        }

    }
};

vi G[30];
unordered_map<int,vi> d; //store the characters in each component
int v[30];


void reset() {
    for (int i=0;i<30;i++) G[i].clear();
    d.clear();
    memset(v,0,sizeof(v));
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        string a,b; cin>>a>>b;
        vi global_reach(20); //for each letter, store the bitmask of letters it directly reaches

        reset();

        dsu dsu(30);
        for (int i=0;i<n;i++)
            if (a[i] != b[i]) {
                global_reach[a[i]-'a'] |= (1 << b[i]-'a');
                dsu.merge(a[i]-'a',b[i]-'a');
            }

        for (int i=0;i<20;i++)
            if (dsu.sz[dsu.find(i)] != 1)
                d[dsu.find(i)].pb(i);



        int res = 0;
        for (auto &pair: d) {
            vi arr = pair.S;
            int dag = 0;
            int sz = arr.size();
            vi is_dag(1<<sz);
            is_dag[0] = 1;

            vi reach(20); //store global_reach bitmask for this component
            for (int i=0;i<sz;i++)
                for (int j=0;j<sz;j++)
                    if (i!=j && global_reach[arr[i]] & (1<<arr[j]))
                        reach[i] |= (1<<j);


            for (int msk=0;msk<(1<<sz);msk++)
                if (is_dag[msk]) {
                    dag = max(dag,__builtin_popcount(msk));
                    for (int j=0;j<sz;j++)
                        if (!(msk&(1<<j)) && ((msk & reach[j]) == 0))
                        is_dag[msk + (1<<j)] = 1;

                }

            res += 2*sz - dag - 1;
        }

        cout << res << '\n';
    }

    return 0;
}