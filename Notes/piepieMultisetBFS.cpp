#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define INF 1000000000

int N,D;
int A[2*MAXN];
int B[2*MAXN];

int dist[2*MAXN];

multiset<int,cmpA> sA; //unvisited/unused Bessie pies
multiset<int,cmpB> sB; //unvisited/unused Elsie pies
struct cmpA
{
    bool operator()(int a,int b) const
    {
        return B[a]<B[b];
    }
};

struct cmpB
{
    bool operator()(int a,int b) const
    {
        return A[a]<A[b];
    }
};
int que[2*MAXN];
int cur,len;

int main()
{
    ofstream fout("piepie.out");
    ifstream fin("piepie.in");

    fin >> N >> D;
    for(int i=0;i<2*N;i++)
    {
        fin >> A[i] >> B[i];
        A[i] = -A[i], B[i] = -B[i]; //we're going backwards, so to maintain origonal conditions we must invert the tastiness
        dist[i] = -1;
    }
    for(int i=0;i<N;i++)
    {
        if(B[i]==0) //set up source nodes, if you get here then it takes only 1 more pie to end
            que[len++] = i, dist[i] = 1;
        else
            sA.insert(i); //otherwise add to set of unvisited nodes
        if(A[N+i]==0)
            que[len++] = N+i, dist[N+i] = 1;
        else
            sB.insert(N+i);
    }
    multiset<int,cmpA>::iterator itA;
    multiset<int,cmpB>::iterator itB;
    while(cur < len) //BFS
    {
        int i = que[cur]; //current index
        if(i < N) //Bessie give to Elsie
        {
            while(1) //remember to dereference (*) itr when not doing s.begin/end()!
            {
                itB = sB.lower_bound(i); //itB will loop through all indicies within A[i] and A[i]+D
                if(itB == sB.end() || A[*itB] > A[i]+D)
                    break;
                dist[*itB] = dist[i] + 1; //update dist
                que[len++] = *itB; //add to queue
                sB.erase(itB); //mark as visited (erase from unvisited)
            }
        }
        else //Elsie give to Bessie
        {
            while(1)
            {
                itA = sA.lower_bound(i);
                if(itA == sA.end() || B[*itA] > B[i]+D)
                    break;
                dist[*itA] = dist[i] + 1;
                que[len++] = *itA;
                sA.erase(itA);
            }
        }
        cur++;
    }
    for(int i=0;i<N;i++) //print bessie pies
        fout << dist[i] << '\n';
}