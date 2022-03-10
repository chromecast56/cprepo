/*
ID: jamesli5
PROG: concom
LANG: C++11
*/
#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> res;
struct edge
{
    int d,w;
};
vector<edge> adj[101];
bool v[101];
int con[101];
void search(int src)
{
    queue<int> q;
    q.push(src);

    while(!q.empty())
    {
        int cur = q.front(); q.pop();
        v[cur] = 1;
        for (auto &e: adj[cur])
        {
            if (v[e.d]) continue;
            con[e.d] += e.w;
            if (con[e.d] > 50)
            {
                res.push_back(make_pair(src,e.d));
                q.push(e.d);
                con[e.d] = -10000;
            }
        }
    }
}
bool comp(pair<int,int> a,pair<int,int> b)
{
    if (a.first==b.first)
        return a.second < b.second;
    return a.first < b.first;
}
int main()
{
    ofstream fout("concom.out");
    ifstream fin("concom.in");

    int n; fin >> n;
    while(n--)
    {
        int a,b,w;
        fin >> a >> b >> w;
        edge e {b,w};
        adj[a].push_back(e);
    }
    for (int i=1;i<=100;i++)
    {
        memset(v,0,sizeof(v));
        memset(con,0,sizeof(con));
        search(i);
    }
    sort(res.begin(),res.end(),comp);

    for (auto &val: res)
        fout << val.first << ' ' << val.second << "\n";

    return 0;
}