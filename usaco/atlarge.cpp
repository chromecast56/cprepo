/*
    Note that this is a tree, graph with N nodes has N-1 edges. WLOG assume the position that Bessie starts at is the root
    This means that all the exit nodes are the leaves in the tree, and Bessie has to beeline to one of the exits (no backtracking)

    This means that a guarenteed solution is to put every farmer at each leaf. This should be intuitive

    Our goal is to take away all the unneeded farmers to get an optimal solution.
    We can see that a farmer is unneeded IFF it never reaches Bessie, basically when some other farmer reaches her first.
    This leads to the algorithm:

    BFS with multiple sources, every exit node and Bessie's position. For each node we mark it with an id
    The v array will store if a node is visited, and if it is, will store which source id visits it first
    Any farmer not "touching" any of the nodes that Bessie reaches is encapsulated by another one,
    and is thus not needed.

    Also, since the graph is a tree there will never be a situation where Bessie can bypass a farmer.

    One thing to keep in mind is because farmers can catch Bessie if they cross the same tunnel at the same time,
    we need to process all the farmers before Bessie in the BFS.
 */
#include <bits/stdc++.h>

using namespace std;

int N,K;
vector<int> adj[100001];
int v[100001];
bool is_needed[100001];

int main()
{
    ofstream fout("atlarge.out");
    ifstream fin("atlarge.in");

    fin >> N >> K;
    for (int i=0;i<N-1;i++)
    {
        int a,b;
        fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    queue<pair<int,int>> q;  //first = cur node, second = color
    for (int i=1;i<=N;i++) //add source nodes
        if (adj[i].size()==1)  //is leaf/exit
            q.push(make_pair(i,i)), v[i]=i;

    q.push(make_pair(K,-1)); //add Bessie node
    v[K] = -1;

    while(!q.empty())
    {
        pair<int,int> cur = q.front();q.pop();
        for (auto &ne: adj[cur.first])
        {
            if (v[ne])
            {
                if (v[ne]==-1) is_needed[cur.second]=1;
                continue;
            }
            q.push(make_pair(ne,cur.second));
            v[ne] = cur.second;
        }
    }
    int res = 0;
    for (int i=1;i<=100000;i++)
        if (is_needed[i]) res++;
    fout << res << "\n";
    return 0;
}