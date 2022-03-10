/*
        Use Tarjan to find the cut nodes and bridges in an undirected graph, NOT SCCs, that is in another one

        Cut nodes: if node is removed then the resulting graph will be disconnected
        Bridges: if edge is removed then the resulting graph will be disconnected

        Currently, it is detecting bridges
 */
#include <cstdio>
#include <iostream>
using namespace std;

int n,m,root,index,fa[1000],dfn[1000],low[1000];
int head[1000],adj[1000],next[1000],tot;

void addedge(int u,int v)
{tot++;adj[tot]=v;next[tot]=head[u];head[u]=tot;
    tot++;adj[tot]=u;next[tot]=head[v];head[v]=tot;}

void dfs(int x)
{
    low[x]=dfn[x]=++index;
    int cnt=0;
    for(int y,i=head[x];i;i=next[i])
    {
        y=adj[i];
        if(y!=fa[x])
        {
            if(!dfn[y])
            {
                cnt++;
                fa[y]=x;
                dfs(y);
                low[x]=min(low[x],low[y]);
                if(low[y]>=dfn[y])
                {
                    cout<<x<<' '<<y<<endl;
                }
            }
            else
            {
                low[x]=min(low[x],dfn[y]);
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        addedge(u,v);
    }
    root=1;
    dfs(root);
    return 0;
}