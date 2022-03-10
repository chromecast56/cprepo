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

vi G[300000];   //stores which node likes node i
vi GR[300000]; //stores what nodes node i likes
int ans[300000];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n,m; cin>>n>>m;
    for (int i=0;i<m;i++) {
        int a,b;
        cin>>a>>b;
        G[a].pb(b);
       // G[b].pb(a);
    }



    return 0;
}