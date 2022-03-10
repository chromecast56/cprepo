#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
typedef vector<int> vi;
const int MAXN = 200100;
const int MAXK = 1000100;

int n,k; int nn;
int global_ans = -1;
int book_keeping = 0; //like a timer
int achievable[MAXK], min_edge[MAXK];
int processed[MAXN]; //keep "visited array" of nodes processed by centroid decomp
int size[MAXN];
vector<pii> adj[MAXN];
void dfspath(int cur,int prev,int cost,int len) { //calculate paths (i.e. calcing answer)
    if (cost>k) return;

    if (achievable[k-cost] == book_keeping)  //a different path of length (k-cost) at this node is found
        if (global_ans==-1 || len+min_edge[k-cost] < global_ans)
            global_ans = len+min_edge[k-cost];
    if (cost==k)
        if (global_ans==-1 || len < global_ans)
            global_ans = len;

    for (auto ne: adj[cur]) if (ne.F!=prev && !processed[ne.F])
        dfspath(ne.F,cur,cost+ne.S,len+1);
}
void dfsdp(int cur,int prev,int cost,int len) { //process dp (i.e calc achievable and min_edge arrays)
    if (cost>k) return;

    if (achievable[cost] < book_keeping) {
        achievable[cost] = book_keeping;
        min_edge[cost] = len;
    }
    else if (len < min_edge[cost]) {
        achievable[cost] = book_keeping;
        min_edge[cost] = len;
    }

    for (auto ne: adj[cur]) if (ne.F!=prev&&!processed[ne.F])
        dfsdp(ne.F,cur,cost+ne.S,len+1);
}
int centroid(int cur,int prev=-1) {
    for (auto ne: adj[cur]) if (ne.F!=prev && !processed[ne.F] && size[ne.F] > nn/2)
        return centroid(ne.F,cur);
    return cur;
}
void dfssize(int cur,int prev=-1) {
    size[cur] = 1;
    for (auto ne: adj[cur]) if (ne.F!=prev && !processed[ne.F]) {
            dfssize(ne.F,cur);
            size[cur] += size[ne.F];
        }
}
int process(int cur)
{
    dfssize(cur);
    nn = size[cur];
    if (size[cur]<=1) return 0;

    int split_node = centroid(cur);
    book_keeping++;
    for (auto ne: adj[split_node])
        if (!processed[ne.F]) {
            dfspath(ne.F,split_node,ne.S,1);
            dfsdp(ne.F,split_node,ne.S,1);
        }
    processed[split_node] = 1;
    for (auto ne: adj[split_node]) if (!processed[ne.F])
        process(ne.F);

    return global_ans;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cin>>n>>k;
    for (int i=0;i<n-1;i++) {
        int a,b,d;
        cin>>a>>b>>d;
        adj[a].emplace_back(b,d);
        adj[b].emplace_back(a,d);
    }

    cout << process(0) << '\n';

    return 0;
}