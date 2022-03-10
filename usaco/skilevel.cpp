#include <bits/stdc++.h>

using namespace std;
const int MAXN = 5;

int R,C,T;
int A[MAXN][MAXN], Q[MAXN][MAXN], res[MAXN*MAXN];

struct Node {
    int x,y;
    Node *pa;

    int rank, sz, min_weight; //rank, component size, min weight to get T
    Node(int x,int y,Node *pa,int rank,int sz,int min_weight)
    : x(x), y(y), pa(pa), rank(rank), sz(sz), min_weight(min_weight) {}
};
struct Edge {
    Node *a, *b;
    int w;
    Edge() {}
    Edge(Node *a, Node *b, int w) : a(a), b(b), w(w) {}
    bool operator<(const Edge &e) const {
        return w < e.w;
    }
};
struct dsu

//DSU CODE
//merge two nodes together, try to balance tree
void merge(Node *a, Node *b) //assumes that nodes a and b are already parents, call find(a)/find(b) if not
{
    if (a->rank < b->rank) {
        a->pa = b;
        b->sz += a->sz;
    }
    else {
        b->pa = a;
        a->sz += b->sz;
        if (a->rank == b->rank)
            a->rank++;
    }
}
//find the parent of a node
Node* find(Node *a)
{
    Node *b = a->pa;
    if (b != b->pa) //recurse to parent
        find(b);

    //PROBLEM SPECIFIC, we know all end-parents have a min_weight, use propagation so that we can call find(a)
    // to set min_weight of all a to p if they arent set
    if (a->min_weight == -1)
        a->min_weight = (b->min_weight == -1)? b->pa->min_weight : b->min_weight;

    //path compression, use propagation to set all parents to end-parent
    a->pa = b->pa;
    return a->pa;
}
vector<edge> eList;
int main()
{
//    ofstream fout("skilevel.out");
//    ifstream fin("skilevel.in");

    ios_base::sync_with_stdio(false); //faster I/O
    cin.tie(NULL); //include only for non-interactive problems

    cin >> R >> C >> T;
    for (int i=0;i<R;i++)
        for (int j=0;j<C;j++)
            cin >> A[i][j];
    for (int i=0;i<R;i++)
        for (int j=0;j<C;j++)
            cin >> Q[i][j];

    for (int i=0;i<R;i++)
        for (int j=0;j<C;j++) {
            point cur = {i,j}, ne;
            if (i < R-1) {
                ne = {i+1,j};
                eList.push_back(edge(cur,ne,abs(A[i][j]-A[ne.x][ne.y])));
            }
            if (j < C-1) {
                ne = {i,j+1};
                eList.push_back(edge(cur,ne,A[i][j]-A[ne.x][ne.y]));
            }
        }

    sort(eList.begin(),eList.end());

    dsu.build();

    for (auto &e: eList) {
        int a = e.a.hash(), b = e.b.hash();
        dsu.merge(a,b);
    }

    long long ress = 0LL;
    for (int i=0;i<R;i++)
        for (int j=0;j<C;j++)
            if (Q[i][j])
                ress += res[dsu.find(i*MAXN+j)];

    cout << ress << '\n';

    return 0;

}