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


int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n,x,m;cin>>n>>x>>m;
        pii res = {-1,-1};
        while(m--) {
            int l,r;cin>>l>>r;
            if (res==make_pair(-1,-1) && l <= x && x <= r)
                res = {l,r};

            if ((r >= res.F && l <= res.S))
                res = {min(res.F,l),max(res.S,r)};
        }

        cout << res.S-res.F+1 << '\n';
    }

    return 0;
}