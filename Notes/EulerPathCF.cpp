/*
                        Problem Summary: You have sticks, and each end has a value (a_i,b_i)
                        You want to arrange the sticks in a circle, tail to tip.

                        The beauty of a tail/tip of two sticks is equal to the maximal 1 bit in a_i ^ b_j
                        Find the configuration that maximizes the minimum beauty in the circle

                        The beauty ranges from 0 to 20. So we can iterate over all target beauty

                        For a given beauty b:
                            Notice that we only care about the first b digits of each a_i. If the first b
                            digits aren't equal for given a_i and a_j, then they shouldn't be paired (as pairing would result in low beauty)
                            If they are, then we could pair them if we wanted to

                        By noticing this equivalence we can then treat all a_i, a_j who have the same first b bits
                        the same. In a problem where the sticks only have 1 value, we would simply determine if all the
                        sticks had the same first b bits.

                        Since they have 2 values, we can notice that the two values of the sticks allow you to "travel"
                        across different b bits. In fact, we can represent this entire problem as a graph in terms
                        of the first b bits, with edges across the sticks (x and y are connected if a_i and b_i are on
                        the the same stick, x = first b bits of a_i)

                        As an example, say we start at a value a_i. All elements with first b bits equal to a_i
                        can be connected to a_i, and their opposite stick values can traversed to. This can be repeated.

                        We reduce the problem to: Given a graph, is there a way to travel along every edge, and
                        end at the starting edge? If so, return the ordering along the verticies.


                        This problem is known as the "Eulerian Cycle" problem, or more generally, "Eulerian Path"
                        https://en.wikipedia.org/wiki/Eulerian_path#:~:text=In%20graph%20theory%2C%20an%20Eulerian,ends%20on%20the%20same%20vertex.

                        A graph is a Eulerian cycle iff:
                            - The degree of every vertex is even
                            - All vertexes are connected to each other

                        A graph is an Eulerian Path iff:
                            - The graph is a Eulerian Cycle OR
                            - There are exactly two nodes with odd degree


                        The Eulerian cycle part can be proven easily... When you pass through a vertex while removing
                        edges, you decrease its degree by 2. This also holds for the starting node, as you start and end on it

                        To find a Eulerian cycle:
                            - Simply do a dfs on the edges of the graph, while removing edges
                            - While backtracking store the verticies (or edges) as the answer

                        If u afraid of cutting off a section of the graph:
                            After you reach the start, the res will fill up until you reach a vertex that still has
                            edges. Then you continue from that vertex and everthing is fine
                            Try a d = {2,6,4} if you're unsure
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;
typedef vector<pii> vpii;

template <class t>          //vector sort template
vector<t> sort(vector<t> &a) {return sort(a.begin(),a.end());}

vector<pii> G[2000000];
int v[2000000];
pii p[2000000];
int n;
void clear() {
    for (int i=0;i<2000000;i++) G[i].clear();
    memset(v,0,sizeof(v));
}
int dfs(int u) { //dfs on edges         // u = {mask, index}
    v[u] = 1;
    for (auto ne: G[u])
        if (!v[ne.F])
            dfs(ne.F);
}
int check(int b) {
    //goal: create a graph based on first b bits, and check if its eulerian (bitmask)
    clear();
    for (int i=1;i<=n;i++) {
        int u = p[i].F & ((1<<b) - 1);
        int v = p[i].S & ((1<<b) - 1);

        G[u].pb({v, i*2-1});                    //we are dealing with pairs 1,2   3,4...   It's hard to find their complements, and hard to find a "pair index" in base 1. Change to base 0 for now
        G[v].pb({u, i*2-2});
    }

    int cnt = 0;
    for (int i=0;i<(1<<b);i++)      //find # components
        if (!v[i] && G[i].size())
            dfs(i), cnt++;
    if (cnt != 1) return 0;           //if cant reach all edges (more than one component)

    for (int i=0;i<(1<<b);i++)
        if (G[i].size() % 2 != 0)       //degree of all verticies must be even
            return 0;

    return 1;
}

vi res;
void path(int cur, int i=-1) {
    while(G[cur].size()) {
        pii e = G[cur].back(); G[cur].pop_back();

        if (v[e.S/2]) continue;         //only in base 0

        v[e.S/2] = 1;
        path(e.F,e.S);
    }

    if (i != -1) {
        res.pb(i);
        res.pb(i^1);    //only in base 0
    }
}
void print(int b) {
    //goal: print the eulerian cycle
    memset(v,0,sizeof(v));

    for (int i=0;i<(1<<b);i++)
        if (G[i].size()) {
            path(i);
            break;
        }

    cout << b << '\n';
    for (int i=0;i<2*n;i++)
        cout << (res[i]+1) << ' '; //0->1
    cout << endl;
}
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    cin>>n;
    for (int i=1;i<=n;i++) {
        int a,b;
        cin>>a>>b;
        p[i] = {a,b};
    }

    for (int b = 20;b>=0;b--)
        if (check(b)) {
            print(b);
            break;
        }

    return 0;
}