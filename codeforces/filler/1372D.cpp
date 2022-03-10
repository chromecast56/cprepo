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

ll a[1000000];
int main()
{
//    ofstream fout("f.out");
//    ifstream fin("f.in");
    ios_base::sync_with_stdio(false);
    cin.tie();

    int n;cin>>n;
    ll res = 0;
    for (int i=1;i<=n;i++) {
        int x;cin>>x;
        if (i%2)    a[(i+1)/2] = x,     res += a[(i+1)/2];
        else        a[(n+1)/2 + i/2] = x;
    }

    for (int i=1;i<=n;i++) a[n+i] = a[i];

    ll t = res;
    for (int i=1+(n+1)/2;i<=2*n;i++)
        t += a[i] - a[i-(n+1)/2], res = max(res,t);

    cout << res;

    return 0;
}