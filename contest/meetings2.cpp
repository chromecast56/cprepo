#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define F first
#define S second
#define pb push_back
typedef vector<int> vi;


int n,L;
vector<pair<int,int>> t; //concatination
vi l,r;
int W=0; //store weight sum
int T=0; //calculate time taken for W/2
struct cow{
    int w,x,d;
    bool operator<(const cow &a) const {
        return x < a.x;
    }
};
cow cows[100010];
int main()
{
    ofstream fout("meetings.out");
    ifstream fin("meetings.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    fin>>n>>L;
    for (int i=0;i<n;i++) {
        int w,x,d;
        fin>>w>>x>>d;

        W += w;
        cows[i] = {w,x,d};
    }

    //THIS code snippet means nothing, but is a useful trick to compress a vector
    vi inds(n); iota(inds.begin(),inds.end(),0); //store increasing sequence (start at 0)
    sort(inds.begin(),inds.end(), [](int a,int b) {return cows[a].x < cows[b].x;}); //define function inside method  (NICE TRICK)
    //

    sort(cows,cows+n); //store right going within 2T in queue
    for (int i=0;i<n;i++) if (cows[i].d==-1) l.pb(cows[i].x); else r.pb(cows[i].x);

    for (int i=0;i<l.size();i++) t.pb({l[i],cows[i].w}); //  |l| cows will end at left barn, we know that these are the leftmost cows
    for (int i=0;i<r.size();i++) t.pb({L-r[i],cows[i+l.size()].w}); //same for r
    sort(t.begin(),t.end());

    int w=0;
    for (int i=0;i<n;i++) {
        w += t[i].S;
        T = t[i].F;
        if (2*w >= W) break;
    }

    queue<int> q;  //store x coordinates in increasing order. The stack will contain all cows within distance T of current cow (that are right going)
    int res = 0;
    for (auto a: cows) {
        if (a.d == -1) { //found left going, trim queue and count intersections
            while (!q.empty() && q.front() + 2*T < a.x)
                q.pop();
            res += q.size();
        }
        else                //found right going, put it in queue
            q.push(a.x);
    }
    fout << res << '\n';

    return 0;
}