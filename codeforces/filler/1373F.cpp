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

ll a[2000100],b[2000100];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        ll s = 0;
        for (int i=0;i<n;i++) cin>>a[i], a[n+i] = a[i], s += a[i];
        for (int i=0;i<n;i++) cin>>b[i], b[n+i] = b[i], s -= b[i];

        ll d = b[0]; //d = the amount left over from previous one
        bool res = 1;
        for (int i=1;i<2*n;i++) {
            d += b[i]-a[i];
            if (d < 0) {
                res = 0;
            }
            d = min(d,b[i]);
        }

        if (s > 0) res = 0;

        cout << (res? "Yes\n" : "No\n");


    }
    return 0;
}