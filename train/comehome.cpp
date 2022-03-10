/*
ID: jamesli5
PROG: comehome
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

int P;
int D[150];
struct edge
{
    char v;
    int w;
};
bool operator <(const edge &a,const edge &b) //usually you have to -pq.poll()!
{
    return a.w > b.w;
}
vector<edge> adj[150];
int main()
{
    ofstream fout("comehome.out");
    ifstream fin("comehome.in");

    fin >> P;
    while(P--)
    {
        char a,b;
        int w;
        fin >> a >> b >> w;
        edge A {a,w}, B{b,w};
        adj[a].push_back(B);
        adj[b].push_back(A);
    }
    priority_queue<edge> pq;
    edge src {'Z',0};
    pq.push(src);

    memset(D,1000000,sizeof(D));
    D['Z'] = 0;
    while(!pq.empty())
    {
        edge cur = pq.top(); pq.pop();
        for (auto &ne: adj[cur.v])
            if (D[cur.v] + ne.w < D[ne.v]) {
                D[ne.v] = D[cur.v] + ne.w;
                pq.push(ne);
            }
    }
    char res_1;
    int res_2 = 1000000;
    for (char i='A';i<'Z';i++)
        if (D[i] < res_2)
        {
            res_1 = i;
            res_2 = D[i];
        }
    fout << res_1 << ' ' << res_2 << "\n";
    return 0;
}