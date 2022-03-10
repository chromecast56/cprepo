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
            int n,m;cin>>n>>m;
            vector<pair<ll,ll>> a(m);
            for(int i=0;i<m;i++) cin>>a[i].F>>a[i].S;
            priority_queue<pair<ll,ll>> pq;

            for (int i=0;i<m;i++) {
                pq.push({a[i].F,i+1});
                pq.push({a[i].S,-i-1});
            }
            ll done=0,tot=0;
            ll ans=0;
            while(pq.size() && done<n) {
                int val=pq.top().F;
                int typ=(pq.top().S<0);
                int ind=abs(pq.top().S)-1;
                pq.pop();
                if(typ==0) {
                    tot+=val;
                    done++;
                    ans=max(ans,tot);
                }
                else {
                    ll tans=tot;
                    if(a[ind].F>val)
                        tans+=(n-done)*val;
                    else
                        tans+=a[ind].F+(n-done-1)*val;

                    ans=max(ans,tans);
                }
            }
            // ans=max(ans,tot);
            cout<<ans<<'\n';

    }

    return 0;
}